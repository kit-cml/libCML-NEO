#ifndef OHARA_RUDY_2011_HPP
#define OHARA_RUDY_2011_HPP

#include "cellmodel.hpp"
#include "enums/enum_Ohara_Rudy_2011.hpp"

class Ohara_Rudy_2011 : public Cellmodel
{
public:
  Ohara_Rudy_2011();
  ~Ohara_Rudy_2011();
  void initConsts();
  void initConsts(double type);
  void initConsts(double type, bool is_dutta);
  void initConsts(double type, double conc, const double *hill, bool is_dutta );
  void computeRates(double TIME, double* CONSTANTS, double* RATES, double* STATES, double* ALGEBRAIC);
  void solveAnalytical( double dt );
  double set_time_step(double TIME,double time_point, 
    double min_time_step, double max_time_step, 
    double min_dV, double max_dV);
private:
  void ___applyDrugEffect(double conc, const double *hill);
  void ___applyDutta();
  void ___initConsts(double type);

};


#endif

