#ifndef CVODE_SOLVER_DATA_HPP
#define CVODE_SOLVER_DATA_HPP

#include <nvector/nvector_serial.h>
#include <sunmatrix/sunmatrix_dense.h>
#include <sunlinsol/sunlinsol_dense.h>

typedef struct {
  void* cvode_mem;
  N_Vector states_vec;
  SUNMatrix matrix;
  SUNLinearSolver solver;
} CVodeSolverData;

#endif
