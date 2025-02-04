#ifndef INPUTOUTPUT_HPP
#define INPUTOUTPUT_HPP

#include "../types/parameter.hpp"
#include "../types/drug_block_input.hpp"
#include "../types/cvar_input.hpp"

#include <cstdio>
#include <vector>

// inputoutput.hpp
// Describes function related to
// I/O capabilities and 
// file/folder manipulations.
// Commonly used POSIX functions, so
// most of the libs only works in *NIX system.

// custom printf for MPI
// to avoid duplicate printing.
// In Windows, this function will be same
// as your usual printf() or fprintf().
// Will be defined for the sake of portability.
void mpi_printf(short node_id, const char *fmt, ...);
void mpi_fprintf(short node_id, FILE *stream, const char *fmt, ...);

// create a directory.
// supporting different OS.
int make_directory(const char* dirname );

// checking file availability
// supporting different OS.
int is_file_existed(const char* pathname);

// parsing drug sample data.
// using generic function
// for both IC50-Hill and hERG vectors.
template <typename RowType, typename InputType>
int get_data_from_file(const char *filename, InputType &vec);
int check_drug_data_content(const Drug_Block_Input &vec, const Parameter *p_param);

// parameter assignment
int assign_params(int *argc, char **argv, Parameter *p_param);

// create concentration directories
int create_concs_directories( std::vector<double> &concs, const char *drug_name );

#endif
