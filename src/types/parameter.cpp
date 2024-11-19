#include "parameter.hpp"

#include <cstdio>
#include "cml_consts.hpp"
#include "../functions/inputoutput.hpp"

void Parameter::init()
{
  bcl = 2000.;
  pace_max = 1000;
  celltype = 0;
  solver_type = 0;
  dt = 0.005;
  dt_min = 0.005;
  dt_max = 1.;
  dvm_min = 0.2;
  dvm_max = 0.8;
  dtw = 2.0;
  stim_dur = 0.5;
  stim_amp_scale = 1.0;
  prior_risk = 2;
  gks_scale = 1.;
  gkr_scale = 1.;
  gk1_scale = 1.;
  gto_scale = 1.;
  pca_scale = 1.;
  gna_scale = 1.;
  gnal_scale = 1.;
  gnab_scale = 1.;
  gcab_scale = 1.;
  gncx_scale = 1.;
  tau_h_scale = 1.;
  is_postprocessing = 0;
  snprintf(mutation_type, sizeof(mutation_type), "%s", "CTL");
  snprintf(user_name, sizeof(user_name), "%s", "johndoe");
  snprintf(hill_file, sizeof(hill_file), "%s", "./chantest_hill/bepridil/IC50_samples10.csv");
  snprintf(herg_file, sizeof(herg_file), "%s", "./chantest_herg/bepridil/boot_pars10.csv");
  snprintf(drug_name, sizeof(drug_name), "%s", "bepridil");
  snprintf(steady_states_init_vals_file, sizeof(steady_states_init_vals_file), "%s", "last_states_%hpaces_ord.dat",pace_max);
  snprintf(concs, sizeof(concs), "%s", "99.0");

  is_ecg = false;
  is_bspm = false;

}

void Parameter::show_val()
{
  mpi_printf( 0, "%s -- %s\n", "user_name", user_name);
  mpi_printf( 0, "%s -- %s\n", "hill_file", hill_file );
  mpi_printf( 0, "%s -- %s\n", "herg_file", herg_file );
  mpi_printf( 0, "%s -- %s\n", "steady-state_init_values_file", steady_states_init_vals_file );
  mpi_printf( 0, "%s -- %hd\n", "celltype", celltype);
  mpi_printf( 0, "%s -- %hd\n", "solver_type", solver_type);
  mpi_printf( 0, "%s -- %s\n", "is_postprocessing", is_postprocessing ? "true" : "false" );
  mpi_printf( 0, "%s -- %lf\n", "basic_cycle_length", bcl);
  mpi_printf( 0, "%s -- %hd\n", "number_of_pacing", pace_max);
  mpi_printf( 0, "%s -- %lf\n", "time_step", dt);
  mpi_printf( 0, "%s -- %lf\n", "time_step_min", dt_min);
  mpi_printf( 0, "%s -- %lf\n", "time_step_max", dt_max);
  mpi_printf( 0, "%s -- %lf\n", "dvm/dt_min", dvm_min);
  mpi_printf( 0, "%s -- %lf\n", "dvm/dt_max", dvm_max);
  mpi_printf( 0, "%s -- %lf\n", "writing_step", dtw);
  mpi_printf( 0, "%s -- %lf\n", "stimulus_duration", stim_dur);
  mpi_printf( 0, "%s -- %lf\n", "stimulus_amplitude_scale", stim_amp_scale);
  mpi_printf( 0, "%s -- %lf\n", "gks_scale", gks_scale);
  mpi_printf( 0, "%s -- %lf\n", "gkr_scale", gkr_scale);
  mpi_printf( 0, "%s -- %lf\n", "gk1_scale", gk1_scale);
  mpi_printf( 0, "%s -- %lf\n", "gto_scale", gto_scale);
  mpi_printf( 0, "%s -- %lf\n", "pca_scale", pca_scale);
  mpi_printf( 0, "%s -- %lf\n", "gna_scale", gna_scale);
  mpi_printf( 0, "%s -- %lf\n", "gnaL_scale", gnal_scale);
  mpi_printf( 0, "%s -- %lf\n", "gnab_scale", gnab_scale);
  mpi_printf( 0, "%s -- %lf\n", "gcab_scale", gcab_scale);
  mpi_printf( 0, "%s -- %lf\n", "gncx_scale", gncx_scale);
  mpi_printf( 0, "%s -- %lf\n", "tau_h_scale", tau_h_scale);
  mpi_printf( 0, "%s -- %s\n", "mutation_type", mutation_type);
  mpi_printf( 0, "%s -- %s\n", "drug_name", drug_name);
  mpi_printf( 0, "%s -- %hd\n", "prior_risk", prior_risk);
  mpi_printf( 0, "%s -- %s\n", "concentrations", concs);


  mpi_printf( 0, "%s -- %s\n", "is_ecg", is_ecg ? "true" : "false" );
  mpi_printf( 0, "%s -- %s\n", "is_bspm", is_bspm ? "true" : "false" );
}
