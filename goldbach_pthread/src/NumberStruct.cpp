#include "NumberStruct.hpp"
#include <stdint.h>

int64_t NumberStruct::get_number(){
    return this->number;
}

void NumberStruct::set_number(int64_t new_number){
    this->number = new_number;
}

NumberArray NumberStruct::get_smaller_primes_array() {
    return this->smallerPrimesArray;
}

NumberArray NumberStruct::get_sums_array() {
    return this->sumsArray;
}

void NumberStruct::append_prime_number(int64_t number) {
    this->smallerPrimesArray.append_number(number);
}

void NumberStruct::append_sums_number(int64_t number) {
    this->sumsArray.append_number(number);
}

void NumberStruct::copy_number_array(NumberStruct*){
}