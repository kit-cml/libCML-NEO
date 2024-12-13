#ifndef PARAMETER_HPP
#define PARAMETER_HPP

struct Parameter
{
  double bcl; // basic cycle length
  short pace_max; // maximum pace
  short solver_type; // 0: Euler, 1: CVode, 2: Analytical, 3: BDF
  short celltype;  // 0: endo, 1: epi, 2: M
  short prior_risk; // 0: low, 1: intermediate, 2: high
  double dt;        // time step
  double dt_min;    // minimum time step (for adaptive dt)
  double dt_max;    // maximum time step (for adaptive dt)
  double dvm_min;    // minimum dVm/dt
  double dvm_max;    // maximum dVm/dt
  double dtw;       // writing step
  double stim_dur;
  double stim_amp_scale;
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

#ifdef TISSUE
  // from this point on,
  // these parameters are belonging to
  // the 2D/3D simulations.
  bool is_crt;
  bool is_ecg;
  bool is_bspm;
  bool is_lbbb;
  bool is_rbbb;
  bool is_s1s2;
  bool is_using_output;
  char fiber_mesh_dir[255];
  char fiber_mesh_file[255];
  char heart_mesh_file[255];
  char torso_mesh_file[255];
  char mesh_type[50];
  char s1_nodes_file[255];
  char s2_nodes_file[255];
  char surface_mesh_file[255];
  char output_mesh_type[50];
  double diffusion_scale;
  double diffusion_scale_fiber;
  double apd_fiber;
  double erp_fiber;
  double twrite_vtk;
  double tmax; // maximum simulation time for 2D/3D
  int dimension;
  int ecgnode[9];
#endif  

  void init();
  void show_val();
};

#endif
