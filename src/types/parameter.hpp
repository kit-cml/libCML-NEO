#ifndef PARAMETER_HPP
#define PARAMETER_HPP

struct Parameter
{
  bool is_print_graph; // TRUE if we want to print graph
  double bcl; // basic cycle length
  short pace_max; // maximum pace
  short solver_type; // 0: Euler, 1: CVode, 2: Analytical, 3: BDF
  short celltype;  // 0: endo, 1: epi, 2: M
  short prior_risk; // 0: low, 1: intermediate, 2: high
  double dt;        // time step
  double dt_min;    // minimum time step (for adaptive dt)
  double dt_max;    // maximum time step (for adaptive dt)
  double dVm_min;    // minimum dVm/dt
  double dVm_max;    // maximum dVm/dt
  double dtw;       // writing step
  bool is_using_steady_states_init_vals;
  bool is_postprocessing;
  // begin conductance scaling vars
  double gks_scale;
  double gkr_scale;
  double gk1_scale;
  double gto_scale;
  double pca_scale;
  double gna_scale;
  double gnal_scale;
  double gnab_scale;
  double gcab_scale;
  double gncx_scale;
  double tau_h_scale;
  // end conductance scaling vars
  char mutation_type[20];
  char hill_file[100];
  char herg_file[100];
  char drug_name[100];
  char concs[50];
  char user_name[20];
  char steady_states_init_vals_file[100];
  void init();
  void show_val();
};

#endif
