#ifndef OHARA_RUDY_CIPA_V1_2017_HPP
#define OHARA_RUDY_CIPA_V1_2017_HPP

#include "cellmodel.hpp"
#include "enums/enum_ohara_rudy_cipa_v1_2017.hpp"

#define EULER

class ohara_rudy_cipa_v1_2017 : public Cellmodel
{
public:
  ohara_rudy_cipa_v1_2017();
  ~ohara_rudy_cipa_v1_2017();
  void initConsts ();
  void initConsts(double ctype);
  void initConsts(double ctype, double conc, const double *hill, const double *herg );
  void initConsts(double ctype, double conc, const double *hill, const double *herg, const double *cvar );
  void computeRates( double TIME, double *CONSTANTS, double *RATES, double *STATES, double *ALGEBRAIC );
  void solveAnalytical( double dt );
  double set_time_step(double TIME,double time_point, 
    double min_time_step, double max_time_step, 
    double min_dV, double max_dV);
private:
  void ___applyCVar(const double *cvar);
  void ___applyDrugEffect(double conc, const double *hill);
  void ___applyHERGBinding(double conc, const double *herg);
  void ___initConsts(double type);
};


#endif

