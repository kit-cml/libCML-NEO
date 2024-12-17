#ifndef TOMEK_MODEL_ENDO_HPP
#define TOMEK_MODEL_ENDO_HPP

#include "cellmodel.hpp"
#include "enums/enum_Tomek_model.hpp"

class Tomek_model : public Cellmodel
{
public:
  Tomek_model();
  ~Tomek_model();
  void initConsts ();
  void initConsts (double celltype);
  void initConsts (double celltype, double conc, const double *hill);
  void initConsts (double celltype, double conc, const double *hill, const double *cvar);
  void computeRates( double TIME, double *CONSTANTS, double *RATES, double *STATES, double *ALGEBRAIC );
  void solveAnalytical( double dt );
  double set_time_step(double TIME,double time_point, 
    double min_time_step, double max_time_step, 
    double min_dV, double max_dV);
private:
  void ___applyCVar(const double *cvar);
  void ___applyDrugEffect(double conc, const double *hill);
  void ___initConsts(double type);
};



#endif

