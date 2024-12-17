#ifndef CELLMODEL_HPP
#define CELLMODEL_HPP

class Cellmodel
{
protected:
  // avoid to create this object
  // since this is an abstract class.
  Cellmodel(){}
public:
  bool is_s1; // used for multicell simulation (1D/2D/3D simulations)
  short algebraic_size;
  short constants_size;
  short states_size;
  double *ALGEBRAIC;
  double *CONSTANTS;
  double *RATES;
  double *STATES;
#ifdef ON_CONSTRUCTION_DO_NOT_REMOVE
  short gates_size;
  short current_size;
  short concs_size;
  char gates_header[255];
  short gates_indices[255];
  char current_header[255];
  short current_indices[255];
  char concs_header[255];
  short concs_indices[255];
#endif
  virtual ~Cellmodel() {}
  virtual void initConsts() = 0;
  virtual void initConsts(double type){}
  virtual void initConsts(double type, bool is_dutta){}
  virtual void initConsts(double type, double conc, const double *hill){}
  virtual void initConsts(double type, double conc, const double *hill, bool is_dutta){}
  virtual void initConsts(double type, double conc, const double *hill, const double* herg){}
  virtual void initConsts(double type, double conc, const double *hill, const double* herg, const double* cvar){}
  virtual void computeRates(double TIME, double *CONSTANTS, double *RATES, double *STATES, double *ALGEBRAIC) = 0;
  virtual void solveAnalytical(double dt) {};
  virtual double set_time_step(double TIME,double time_point, 
    double min_time_step, double max_time_step, 
    double min_dV, double max_dV) {return 0.005;};
};


#endif
