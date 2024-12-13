#ifndef CML_CONSTS_HPP
#define CML_CONSTS_HPP

// Collection of namespaces to define global constants.
// Please put your constants variable according 
// to the category provided below.
// If you need to define a new category, let me know.

// Naming of namespace should be one word and simple.
// Namespace name only have small letters, short, and concise.
// Constants name should have only capital letters and underscore
// as the separator.

namespace cml{
  
  namespace math{
    // to normalize the small values
    // so it can compressed the file size.
    // Information of the scaling should be
    // described in the header result.
    static const int MILLI_TO_NANO = 1000000;
    static const int MICRO_TO_NANO = 1000;
    static const double SECOND_TO_MINUTE = 0.01666666667;
  }
  
  namespace commons{
    // the default constants of result folder
    static const char *RESULT_FOLDER = "./result/";
    // master node that usually used in the MPI program
    static const int MASTER_NODE = 0;
  }

  namespace tissue{
    static const int VTK_SCALAR_OUTPUT_SIZE = 4;
    static const char* VTK_SCALAR_OUTPUT_LABEL[4] = {"V","cai","qnet","qnet_apd"};
  }

}


#endif
