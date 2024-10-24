#ifndef ODESOLVER_HPP
#define ODESOLVER_HPP

#include "../cellmodels/cellmodel.hpp"

class OdeSolver{
protected:
  // avoid to create this object
  // since this is an abstract class.
  OdeSolver(){}
public:
  Cellmodel *cell_object;
  virtual void initialize( Cellmodel *cell_object ) = 0;
  virtual void initialize( double tstart, double dt, Cellmodel *cell_object ){};
  // only solve for one step at a time.
  virtual void solve( double dt ) = 0;
};

#endif
