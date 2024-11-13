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

// Initialize CVode setting for p_cvode.
void init_cvode(CVodeSolverData* p_cvode, Cellmodel* p_cell, double tcurr);

// Change the maximum time step according to
// the specified conditions.
void set_dt_cvode(CVodeSolverData* p_cvode, double tcurr, double time_point, double bcl,
double dt_min, double dt_max, double *dt);

// Solve the ODE using CVode() function.
// This function implicitly calls the rhs_fn() function.
int solve_cvode(CVodeSolverData* p_cvode, Cellmodel* p_cell, double tnext, double *tcurr);

// Cleanup the memory after usage.
void clean_cvode(CVodeSolverData* p_cvode);


#endif
