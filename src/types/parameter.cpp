#include "parameter.hpp"

#include <cstdio>
#include "../functions/inputoutput.hpp"

void Parameter::init()
{
  is_print_graph = true;
  bcl = 2000.;
  pace_max = 1000;
  celltype = 0;
  solver_type = 0;
  dt = 0.005;
  dt_min = 0.005;
  dt_max = 1.;
  dVm_min = 0.2;
  dVm_max = 0.8;
  dtw = 2.0;
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
  is_using_steady_states_init_vals = 0;
  is_postprocessing = 0;
  snprintf(mutation_type, sizeof(mutation_type), "%s", "CTL");
  snprintf(user_name, sizeof(user_name), "%s", "johndoe");
  snprintf(hill_file, sizeof(hill_file), "%s", "./chantest_hill/bepridil/IC50_samples10.csv");
  snprintf(herg_file, sizeof(herg_file), "%s", "./chantest_herg/bepridil/boot_pars10.csv");
  snprintf(drug_name, sizeof(drug_name), "%s", "bepridil");
  snprintf(steady_states_init_vals_file, sizeof(steady_states_init_vals_file), "%s", "last_states_%hpaces_ord.dat",pace_max);
  snprintf(concs, sizeof(concs), "%s", "99.0");
}

void Parameter::show_val()
{
  mpi_printf( 0, "%s -- %s\n", "User Name", user_name);
  mpi_printf( 0, "%s -- %s\n", "Hill File", hill_file );
  mpi_printf( 0, "%s -- %s\n", "hERG File", herg_file );
  mpi_printf( 0, "%s -- %s\n", "Steady-state Init Values File", steady_states_init_vals_file );
  mpi_printf( 0, "%s -- %hd\n", "Celltype", celltype);
  mpi_printf( 0, "%s -- %hd\n", "Solver_Type", solver_type);
  mpi_printf( 0, "%s -- %s\n", "Is_Print_Graph", is_print_graph ? "true" : "false" );
  mpi_printf( 0, "%s -- %s\n", "Is_Using_Steady_State_Init_Values", is_using_steady_states_init_vals ? "true" : "false" );
  mpi_printf( 0, "%s -- %s\n", "Is_Postprocessing", is_postprocessing ? "true" : "false" );
  mpi_printf( 0, "%s -- %lf\n", "Basic_Cycle_Length", bcl);
  mpi_printf( 0, "%s -- %hd\n", "Number_of_Pacing", pace_max);
  mpi_printf( 0, "%s -- %lf\n", "Time_Step", dt);
  mpi_printf( 0, "%s -- %lf\n", "Time_Step_Min", dt_min);
  mpi_printf( 0, "%s -- %lf\n", "Time_Step_Max", dt_max);
  mpi_printf( 0, "%s -- %lf\n", "dVm/dt_Min", dVm_min);
  mpi_printf( 0, "%s -- %lf\n", "dVm/dt_Max", dVm_max);
  mpi_printf( 0, "%s -- %lf\n", "Writing_Step", dtw);
  mpi_printf( 0, "%s -- %lf\n", "GKs_Scale", gks_scale);
  mpi_printf( 0, "%s -- %lf\n", "GKr_Scale", gkr_scale);
  mpi_printf( 0, "%s -- %lf\n", "GK1_Scale", gk1_scale);
  mpi_printf( 0, "%s -- %lf\n", "Gto_Scale", gto_scale);
  mpi_printf( 0, "%s -- %lf\n", "PCa_Scale", pca_scale);
  mpi_printf( 0, "%s -- %lf\n", "GNa_Scale", gna_scale);
  mpi_printf( 0, "%s -- %lf\n", "GNaL_Scale", gnal_scale);
  mpi_printf( 0, "%s -- %lf\n", "GNab_Scale", gnab_scale);
  mpi_printf( 0, "%s -- %lf\n", "GCab_Scale", gcab_scale);
  mpi_printf( 0, "%s -- %lf\n", "Gncx_Scale", gncx_scale);
  mpi_printf( 0, "%s -- %lf\n", "Tau_h_Scale", tau_h_scale);
  mpi_printf( 0, "%s -- %s\n", "Mutation_Type", mutation_type);
  mpi_printf( 0, "%s -- %s\n", "Drug_Name", drug_name);
  mpi_printf( 0, "%s -- %hd\n", "Prior_Risk", prior_risk);
  mpi_printf( 0, "%s -- %s\n", "Concentrations", concs);

}
