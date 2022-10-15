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

    int64_t get_number();

    NumberArray get_smaller_primes_array();

    NumberArray get_sums_array();

    void append_prime_number(int64_t number);

    void append_sums_number(int64_t number);

    void copy_number_array(NumberStruct*);
};

#endif