#include "helper_math.hpp"

#include "../types/cellmodels/cellmodel.hpp"


void solveEuler(double dt, Cellmodel* user_data)
{
  short idx;
  for( idx = 0; idx < user_data->states_size; idx++ ) user_data->STATES[idx] += (user_data->RATES[idx]*dt);
}
