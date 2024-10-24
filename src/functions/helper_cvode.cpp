#include "helper_cvode.hpp"

#include "inputoutput.hpp"
#include "../types/cellmodels/cellmodel.hpp"
#include "../types/cml_consts.hpp"
#include "../types/cvode_solver_data.hpp"

#include <algorithm>
#include <cmath>
#include <cvode/cvode.h>
#include <nvector/nvector_serial.h>
#include <sunmatrix/sunmatrix_dense.h>
#include <sunlinsol/sunlinsol_dense.h>


int rhs_fn(realtype time,
    N_Vector y,
    N_Vector ydot,
    void* user_data)
{
  Cellmodel* data = (Cellmodel*)user_data;
  data->computeRates(time,
      data->CONSTANTS,
      N_VGetArrayPointer_Serial(ydot),
      N_VGetArrayPointer_Serial(y),
      data->ALGEBRAIC);  
  return 0;
}

void errorHandler(int pErrorCode, const char *pModule, const char *pFunction,
                  char *pErrorMessage, void *pUserData)
{
  if (pErrorCode != CV_WARNING) {
    mpi_printf(cml::commons::MASTER_NODE,"CVode Error message: %s\n", pErrorMessage);
  }
}

void init_cvode(CVodeSolverData* p_cvode, Cellmodel* p_cell, double tcurr)
{
  p_cvode->cvode_mem = CVodeCreate(CV_BDF);
  p_cvode->states_vec = N_VMake_Serial(p_cell->states_size, p_cell->STATES);
  p_cvode->matrix = SUNDenseMatrix(p_cell->states_size, p_cell->states_size);
  p_cvode->solver = SUNLinSol_Dense(p_cvode->states_vec, p_cvode->matrix);
  CVodeInit(p_cvode->cvode_mem, rhs_fn, tcurr, p_cvode->states_vec);
  CVodeSetUserData(p_cvode->cvode_mem, p_cell);
  CVodeSStolerances(p_cvode->cvode_mem, 1.0e-7, 1.0e-7);
  CVodeSetLinearSolver(p_cvode->cvode_mem, p_cvode->solver, p_cvode->matrix);
  CVodeSetErrHandlerFn(p_cvode->cvode_mem, errorHandler, p_cell);
}

void set_dt_cvode(CVodeSolverData* p_cvode, double tcurr, double time_point, double bcl,
double dt_min, double dt_max, double *dt )
{
  if (tcurr <= time_point || (tcurr - floor(tcurr / bcl) * bcl) <= time_point){
    CVodeSetMaxStep(p_cvode->cvode_mem, dt_min);
    *dt = dt_min;
  }
  else{
    CVodeSetMaxStep(p_cvode->cvode_mem, dt_max);
    //*dt = dt_max;
  }
}

int solve_cvode(CVodeSolverData* p_cvode, Cellmodel* p_cell, double tnext, double *tcurr)
{
  int retval = 0;

  // variables for calculating RATES
  // without calling computeRates() again.
  double ONE_OVER_DT = 1/( tnext-(*tcurr) );
  double *old_states = new double[p_cell->states_size];
  std::copy(p_cell->STATES, p_cell->STATES+p_cell->states_size, old_states );

  CVode(p_cvode->cvode_mem, tnext, p_cvode->states_vec, tcurr, CV_NORMAL);
  if( retval != CV_SUCCESS ){
    return 1;
  }
  for( short idx = 0; idx < p_cell->states_size; idx++ ){
    p_cell->RATES[idx] = ONE_OVER_DT * (p_cell->STATES[idx]-old_states[idx]);
  }

  delete[] old_states;
  return retval;
}

void clean_cvode(CVodeSolverData* p_cvode)
{
  SUNMatDestroy(p_cvode->matrix);
  SUNLinSolFree(p_cvode->solver);
  N_VDestroy(p_cvode->states_vec);
  CVodeFree(&(p_cvode->cvode_mem));
}
