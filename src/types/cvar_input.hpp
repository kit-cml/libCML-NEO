#ifndef CVAR_INPUT_HPP
#define CVAR_INPUT_HPP

#include <vector>

// data structure for IC50-Hill pairs
// and also hERG parameters.
struct Cvar_Row { double data[18]; };
typedef std::vector< Cvar_Row > Cvar_Input;

#endif
