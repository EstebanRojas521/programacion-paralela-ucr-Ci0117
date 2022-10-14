#ifndef NUMBER_STRUCT_HPP
#define NUMBER_STRUCT_HPP

#include <stdint.h>
#include <cstdlib>
#include "NumberArray.hpp"

class NumberStruct{

    int64_t number;
    NumberArray smallerPrimesArray;
    NumberArray sumsArray;

    public:
    NumberStruct();
    ~NumberStruct();

    void copy_number_array(NumberStruct*);
};

#endif