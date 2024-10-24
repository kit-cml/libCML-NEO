#ifndef HELPER_MATH_HPP
#define HELPER_MATH_HPP

#include "../types/cellmodels/cellmodel.hpp"

// helper_math.hpp
//
// Contains functions for complex mathematical operations.

void gaussElimination(double *A, double *b, double *x, int N);
void numericalJacobian(double time, double *y, double **jac, double epsilon, Cellmodel *user_data);
void solveBDF1(double time, double dt, double epsilon, Cellmodel* user_data);
void solveEuler(double dt, Cellmodel* user_data);

#endif
