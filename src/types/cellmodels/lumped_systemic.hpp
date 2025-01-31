#ifndef LUMPED_SYSTEMIC_HPP
#define LUMPED_SYSTEMIC_HPP

#include "cellmodel.hpp"

class lumped_systemic : public Cellmodel
{
public:
  lumped_systemic();
  ~lumped_systemic();
  void initConsts ();
  void computeRates( double TIME, double *CONSTANTS, double *RATES, double *STATES, double *ALGEBRAIC );
  void solveAnalytical( double dt );
};


#endif

