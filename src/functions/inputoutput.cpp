#include "inputoutput.hpp"
#include "../types/mpi_profile.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <vector>

// to make it more "portable" between OSes.
#if defined _WIN32
  #include <direct.h>
  #define snprintf _snprintf
  #define vsnprintf _vsnprintf
  #define strcasecmp _stricmp
  #define strncasecmp _strnicmp
#else
  #include <dirent.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void mpi_printf(short node_id, const char *fmt, ...)
{
#ifndef _WIN32
  if(MPI_Profile::rank == node_id){
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
  }
#else
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);  
#endif
}

void mpi_fprintf(short node_id, FILE *stream, const char *fmt, ...)
{
#ifndef _WIN32
  if(MPI_Profile::rank == node_id){
    va_list args;
    va_start(args, fmt);
    vfprintf(stream, fmt, args);
    va_end(args);
  }
#else
  va_list args;
  va_start(args, fmt);
  vfprintf(stream, fmt, args);
  va_end(args);  
#endif
}

int make_directory(const char* dirname )
{
#if defined _WIN32
  return _mkdir(dirname);
#else
  return mkdir(dirname, 0775);
#endif  
}

int is_file_existed(const char* pathname)
{
#if defined _WIN32
  struct _stat buf;
  return _stat( pathname, &buf );
#else
  struct stat st = {0};
  return stat(pathname, &st);
#endif
}

int get_drug_data_from_file(const char *file_name, Drug_Block_Input &vec)
{
  FILE *fp_drugs;
  char *token, buffer[255];
  Drug_Row temp_array;
  short idx;

  if( (fp_drugs = fopen(file_name, "r")) == NULL){
    printf("Cannot open file %s\n", file_name);
    return 1;
  }

  fgets(buffer, sizeof(buffer), fp_drugs); // skip header
  while( fgets(buffer, sizeof(buffer), fp_drugs) != NULL )
  { // begin line reading
    token = strtok( buffer, "," );
    idx = 0;
    while( token != NULL )
    { // begin data tokenizing
      temp_array.data[idx++] = strtod(token, NULL);
      token = strtok(NULL, ",");
    } // end data tokenizing
    vec.push_back(temp_array);
  } // end line reading

  return 0;
}

int check_drug_data_content(const Drug_Block_Input &vec, const Parameter *p_param)
{
  if(vec.size() == 0){
    mpi_printf(0, "Something problem with the drug file!\n");
    return 1;
  }
  else if(vec.size() > 2000){
    mpi_printf(0, "Too much input! Maximum sample data is 2000!\n");
    return 1;
  }
  else if(p_param->pace_max < 750 && p_param->pace_max > 1000){
    mpi_printf(0, "Make sure the maximum pace is around 750 to 1000!\n");
    return 1;
  }
  else if(MPI_Profile::size > vec.size()){
    mpi_printf(0, "%s\n%s\n",
                "Overflow of MPI Process!",
                "Make sure MPI Size is less than or equal the number of sample");
    return 1;
  }
  return 0;
}

int assign_params(int *argc, char *argv[], Parameter *p_param)
{
  bool is_default;
  char buffer[100];
  char key[100];
  char value[100];
  char file_name[150] = "nofile";
  FILE *fp_inputdeck;

  // parameters from arguments
  for (int idx = 1; idx < *argc; idx += 2) {
  if (!strcasecmp(argv[idx], "-input_deck"))
    strncpy(file_name, argv[idx + 1], sizeof(file_name));
  }  

  is_default = false;
  fp_inputdeck = fopen( file_name, "r");
  if(fp_inputdeck == NULL){
  mpi_fprintf(0, stderr, "Cannot open input deck file %s!!!\nUse default value as the failsafe.\n", file_name);
  is_default = true;
  }

  // read input_deck line by line
  // and store each line to the buffer
  while ( is_default == false && fgets( buffer, 100, fp_inputdeck ) != NULL ) {
    sscanf( buffer, "%s %*s %s", key, value );
    if (strcasecmp(key, "celltype") == 0) {
      p_param->celltype = strtol( value, NULL, 10 );
    }
    else if (strcasecmp(key, "solver_type") == 0) {
      p_param->solver_type = strtol( value, NULL, 10 );
    }
    else if (strcasecmp(key, "user_name") == 0) {
      strncpy( p_param->user_name, value, sizeof(p_param->user_name));
    }
    else if (strcasecmp(key, "basic_cycle_length") == 0) {
      p_param->bcl = strtod( value, NULL );
    }
    else if (strcasecmp(key, "number_of_pacing") == 0) {
      p_param->pace_max = strtol( value, NULL, 10 );
    }
    else if (strcasecmp(key, "time_step") == 0) {
      p_param->dt = strtod( value, NULL );
    }
    else if (strcasecmp(key, "time_step_min") == 0) {
      p_param->dt_min = strtod( value, NULL );
    }
    else if (strcasecmp(key, "time_step_max") == 0) {
      p_param->dt_max = strtod( value, NULL );
    }
    else if (strcasecmp(key, "dvm/dt_min") == 0) {
      p_param->dvm_min = strtod( value, NULL );
    }
    else if (strcasecmp(key, "dvm/dt_max") == 0) {
      p_param->dvm_max = strtod( value, NULL );
    }
    else if (strcasecmp(key, "writing_step") == 0) {
      p_param->dtw = strtod( value, NULL );
    }
    else if (strcasecmp(key, "drug_name") == 0) {
      strncpy( p_param->drug_name, value, sizeof(p_param->concs) );
    }
    else if (strcasecmp(key, "concentrations") == 0) {
      strncpy( p_param->concs, value, sizeof(p_param->concs) );
    }
    else if (strcasecmp(key, "prior_risk") == 0) {
      p_param->prior_risk = strtol( value, NULL, 10 );;
    }
    else if (strcasecmp(key, "gks_scale") == 0) {
      p_param->gks_scale = strtod( value, NULL);
    }
    else if (strcasecmp(key, "gkr_scale") == 0) {
      p_param->gkr_scale = strtod( value, NULL);
    }
    else if (strcasecmp(key, "gk1_scale") == 0) {
      p_param->gk1_scale = strtod( value, NULL);
    }
    else if (strcasecmp(key, "gto_scale") == 0) {
      p_param->gto_scale = strtod( value, NULL);
    }
    else if (strcasecmp(key, "pca_scale") == 0) {
      p_param->pca_scale = strtod( value, NULL);
    }
    else if (strcasecmp(key, "gna_scale") == 0) {
      p_param->gna_scale = strtod( value, NULL);
    }
    else if (strcasecmp(key, "gnal_scale") == 0) {
      p_param->gnal_scale = strtod( value, NULL);
    }
    else if (strcasecmp(key, "gnab_scale") == 0) {
      p_param->gnab_scale = strtod( value, NULL);
    }
    else if (strcasecmp(key, "gcab_scale") == 0) {
      p_param->gcab_scale = strtod( value, NULL);
    }
    else if (strcasecmp(key, "gncx_scale") == 0) {
      p_param->gncx_scale = strtod( value, NULL);
    }
    else if (strcasecmp(key, "tau_h_scale") == 0) {
      p_param->tau_h_scale = strtod( value, NULL);
    }
    else if (strcasecmp(key, "hill_hile") == 0){
      strncpy( p_param->hill_file, value, sizeof(p_param->hill_file));
    }
    else if (strcasecmp(key, "herg_file") == 0){
      strncpy( p_param->herg_file, value, sizeof(p_param->herg_file));
    }
    else if (strcasecmp(key, "mutation_type") == 0){
      strncpy( p_param->mutation_type, value, sizeof(p_param->mutation_type));
    }
    else if (strcasecmp(key, "steady_states_init_vals_file") == 0 && strlen(value) > 0){
      strncpy( p_param->steady_states_init_vals_file, value, sizeof(p_param->steady_states_init_vals_file));
    }
    else if (strcasecmp(key, "is_postprocessing") == 0){
      p_param->is_postprocessing = strtol( value, NULL, 10 );
    }

  
  }

  if( is_default == false ) fclose( fp_inputdeck );
  
  return 0;
}

int create_concs_directories( std::vector<double> &concs, const char *drug_name )
{
  // constants to avoid magic values
  static const char *RESULT_FOLDER_PATH = "result";
  static const double CONTROL_CONC = 0.;
  char buffer[255];
  char create_time_str[9];
  int idx;

  make_directory(RESULT_FOLDER_PATH);
  snprintf( buffer, sizeof(buffer), "%s/%s", RESULT_FOLDER_PATH, drug_name);
  if(is_file_existed(RESULT_FOLDER_PATH) == 0) make_directory(buffer);
  snprintf( buffer, sizeof(buffer), "%s/%s/%.0lf", RESULT_FOLDER_PATH, drug_name, CONTROL_CONC);
  if(is_file_existed(RESULT_FOLDER_PATH) == 0) make_directory(buffer);
  for( idx = 0; idx < concs.size(); idx++ )
  { // begin concentration loop
    snprintf( buffer, sizeof(buffer), "%s/%s/%.0lf", RESULT_FOLDER_PATH, drug_name, concs[idx] );
    if(is_file_existed(RESULT_FOLDER_PATH) == 0) make_directory(buffer);
  } // end concentration loop

  return 0;
}
