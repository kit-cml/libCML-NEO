#ifndef DRUG_BLOCK_INPUT_HPP
#define DRUG_BLOCK_INPUT_HPP

#include <vector>

// data structure for IC50-Hill pairs
// and also hERG parameters.
typedef struct row_data { double data[14]; } Drug_Row;
typedef std::vector< Drug_Row > Drug_Block_Input;

#endif
