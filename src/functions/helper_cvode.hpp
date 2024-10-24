#ifndef HELPER_CVODE_HPP
#define HELPER_CVODE_HPP

// helper_cvode.hpp
//
// Contains functions for solving ODE using CVode.

#include <nvector/nvector_serial.h>

#include "../types/cvode_solver_data.hpp"
#include "../types/cellmodels/cellmodel.hpp"

// RHS function for CVode.
// This is the function prototype defined by CVode.
// Do not change this.
int rhs_fn(realtype time,
    N_Vector y,
    N_Vector ydot,
    void* user_data);

// Error handler function for CVode.
// This is the function prototype defined by CVode.
// Do not change this.
void errorHandler(int pErrorCode, const char *pModule, const char *pFunction,
                  char *pErrorMessage, void *pUserData);

void init_cvode(CVodeSolverData* p_cvode, Cellmodel* p_cell, double tcurr);

void set_dt_cvode(CVodeSolverData* p_cvode, double tcurr, double time_point, double bcl,
double dt_min, double dt_max, double *dt);

int solve_cvode(CVodeSolverData* p_cvode, Cellmodel* p_cell, double tnext, double *tcurr);

void clean_cvode(CVodeSolverData* p_cvode);


#endif
