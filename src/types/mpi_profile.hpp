#ifndef MPI_PROFILE_HPP
#define MPI_PROFILE_HPP

// mpi_profile.hpp
// Global structure of accessing MPI members.

struct MPI_Profile
{
  static char host_name[255];
  static int host_name_len;
  static int rank;
  static int size;
};

#endif
