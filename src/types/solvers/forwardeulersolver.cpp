#include "forwardeulersolver.hpp"

ForwardEulerSolver::ForwardEulerSolver()
{

}

void ForwardEulerSolver::initialize( Cellmodel *cell_object )
{
  this->cell_object = cell_object;
}

void ForwardEulerSolver::solve( double dt )
{
  short idx;
  for(idx = 0; idx < this->cell_object->states_size; idx++) {
    this->cell_object->STATES[idx] += (this->cell_object->RATES[idx]*dt);
  }
}
