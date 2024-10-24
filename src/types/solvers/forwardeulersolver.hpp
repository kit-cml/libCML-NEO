#ifndef FORWARDEULERSOLVER_HPP
#define FORWARDEULERSOLVER_HPP

#include "odesolver.hpp"

class ForwardEulerSolver : public OdeSolver
{
public:
  ForwardEulerSolver();
  ~ForwardEulerSolver();
  void initialize( Cellmodel *cell_object );
  void solve( double tcurr );
};


#endif

