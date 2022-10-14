#ifndef NUMBER_STRUCT_HPP
#define NUMBER_STRUCT_HPP

#include <stdint.h>
#include <cstdlib>
#include "number_array.hpp"

class number_struct{

    int64_t number;
    number_array smaller_primes_array;
    number_array sums_array;

    public:
    number_struct();
    ~number_struct();

    void copy_number_array(number_struct*);
};

#endif