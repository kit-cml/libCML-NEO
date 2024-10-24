#include "helper_math.hpp"

#include "../types/cellmodels/cellmodel.hpp"

#include <cmath>
#include <cstdlib>

void gaussElimination(double *A, double *b, double *x, int N) {
  // Using A as a flat array to represent an N x N matrix
  for (int i = 0; i < N; i++) {
    // Search for maximum in this column
    double maxEl = fabs(A[i*N + i]);
    int maxRow = i;
    for (int k = i + 1; k < N; k++) {
      if (fabs(A[k*N + i]) > maxEl) {
        maxEl = fabs(A[k*N + i]);
        maxRow = k;
      }
    }

    // Swap maximum row with current row (column by column)
    for (int k = i; k < N; k++) {
      double tmp = A[maxRow*N + k];
      A[maxRow*N + k] = A[i*N + k];
      A[i*N + k] = tmp;
    }
    double tmp = b[maxRow];
    b[maxRow] = b[i];
    b[i] = tmp;

    // Make all rows below this one 0 in current column
    for (int k = i + 1; k < N; k++) {
      double c = -A[k*N + i] / A[i*N + i];
      for (int j = i; j < N; j++) {
        if (i == j) {
          A[k*N + j] = 0;
        } else {
          A[k*N + j] += c * A[i*N + j];
        }
      }
      b[k] += c * b[i];
    }
  }

  // Solve equation Ax=b for an upper triangular matrix A
  for (int i = N - 1; i >= 0; i--) {
    x[i] = b[i] / A[i*N + i];
    for (int k = i - 1; k >= 0; k--) {
      b[k] -= A[k*N + i] * x[i];
    }
  }
}

void numericalJacobian(double time, double *y, double **jac, double epsilon, Cellmodel *p_cell){
  double g0[p_cell->states_size]; // to store rates
  // rhs_fn(time,y,g0,data);
  p_cell->computeRates(time,p_cell->CONSTANTS,g0,y,p_cell->ALGEBRAIC);
  for (int j = 0; j < p_cell->states_size; ++j) {
    double y_perturbed[p_cell->states_size];
    for (int k = 0; k < p_cell->states_size; ++k) {
        y_perturbed[k] = y[k];
    }
    y_perturbed[j] += epsilon; // y(i+1) - y(i) = epsilon * y(i)
    double g_perturbed[p_cell->states_size]; // to store rates
    // rhs_fn(time,y_perturbed,g_perturbed,data);
    p_cell->computeRates(time,p_cell->CONSTANTS,g_perturbed,y_perturbed,p_cell->ALGEBRAIC);
    for (int i = 0; i < p_cell->states_size; ++i) {
      jac[i][j] = (g_perturbed[i] - g0[i]) / (epsilon); // dg/dy = ( g(y(i+1)) - g(y(i)) ) / ( epsilon * y(i) ) 
    }
  }
}

void solveBDF1(double time, double dt, double epsilon, Cellmodel *p_cell){
  // Initialize solution
  double y[p_cell->states_size];
  double y_new[p_cell->states_size];
  for (int i = 0; i < p_cell->states_size; ++i) {
      y[i] = p_cell->STATES[i];
  }
  // Newton-Raphson method variables
  double F[p_cell->states_size];
  double **Jc = new double*[p_cell->states_size];
  double Jcf[p_cell->states_size*p_cell->states_size]; // flatten of Jc
  for (int i = 0; i < p_cell->states_size; i++){
    Jc[i] = new double[p_cell->states_size];
  }
  double delta[p_cell->states_size];
  // Initial guess
  for (int i = 0; i < p_cell->states_size; ++i) {
    y_new[i] = y[i]; // Initial guess
  }
  // Newton-Raphson iterations
  for (int iter = 0; iter < 100; ++iter) { 
    // rhs_fn(time,y_new,F,data);
    p_cell->computeRates(time,p_cell->CONSTANTS,F,y_new,p_cell->ALGEBRAIC);
    for (int i = 0; i < p_cell->states_size; ++i) {
      F[i] = y_new[i] - y[i] - dt * F[i];
    }
    // jacobian(y_new, J); // or use numericalJacobian(y_new, J)
    numericalJacobian(time,y_new,Jc,epsilon,p_cell);
    for (int i = 0; i < p_cell->states_size; ++i) {
      for (int j = 0; j < p_cell->states_size; ++j) {
        Jcf[i * p_cell->states_size + j] = (i == j ? 1.0 : 0.0) - dt * Jc[i][j];
      }
    }
    gaussElimination(Jcf,F,delta,p_cell->states_size);
    for (int i = 0; i < p_cell->states_size; ++i) {
      y_new[i] -= delta[i];
    }
    double norm = 0.0;
    for (int i = 0; i < p_cell->states_size; i++){
      norm = norm + delta[i] * delta[i];
    }
    norm = sqrt(norm);
    if (norm < 1e-6){
      break;
    }    
  }
  for (int i = 0; i < p_cell->states_size; i++){
    p_cell->STATES[i] = y_new[i];
  }
  for (int i = 0; i < p_cell->states_size; i++){
    delete[] Jc[i];
  }
  delete[] Jc;
}

void solveEuler(double dt, Cellmodel* user_data)
{
  short idx;
  for( idx = 0; idx < user_data->states_size; idx++ ) user_data->STATES[idx] += (user_data->RATES[idx]*dt);
}
