#ifndef LAND_ET_AL_2016_HPP
#define LAND_ET_AL_2016_HPP

#include "cellmodel.hpp"
#include "enums/enum_Land_et_al_2016.hpp"

class Land_et_al_2016 : public Cellmodel
{
public:
  Land_et_al_2016();
  ~Land_et_al_2016();
  void initConsts ();
  void computeRates( double TIME, double *CONSTANTS, double *RATES, double *STATES, double *ALGEBRAIC );
  void solveAnalytical( double dt );
};


#endif

