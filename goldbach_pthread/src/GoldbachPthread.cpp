#include "GoldbachPthread.hpp"
#include "NumberStruct.hpp"
#include "NumberArray.hpp"
#include <iostream>
#include <cstdlib>
#include <stdint.h>

GoldbachPthread::GoldbachPthread(){
    this->totalNumbers = 0;
    this->totalSums = 0;
}

GoldbachPthread::~GoldbachPthread(){
    this->totalNumbers = 0;
    this->totalSums = 0;
    for(int64_t i = 0; i < this->totalNumbers; i++){
        delete this->numberStructArray[i];
    }
}

int64_t GoldbachPthread::is_prime(int64_t number){
    int64_t is_prime = EXIT_SUCCESS;

    for (int64_t i = 2; i < number; i++){
        if ((number % i) == 0) {
            is_prime = EXIT_FAILURE;
        }
    }
    return is_prime;
}
int64_t GoldbachPthread::calculate_smaller_primes(NumberStruct* number_struct){
    int64_t error = EXIT_SUCCESS;
    int64_t struct_number = (int64_t)abs((int)number_struct->get_number());
    for (int64_t i = 2; i < struct_number; i++) {
        if (is_prime(i) == 0) {
            number_struct->append_prime_number(i);
        }
    }
}

int64_t GoldbachPthread::check_repeated_even(NumberArray*, int64_t, int64_t){
}

int64_t GoldbachPthread::check_repeated_uneven(NumberArray*, int64_t, int64_t, int64_t){
}

int64_t GoldbachPthread::process_even_number(NumberStruct*){
}

int64_t GoldbachPthread::process_uneven_number(NumberStruct*){
}

void GoldbachPthread::print64_t_goldbach_even(NumberStruct*){
}

void GoldbachPthread::print64_t_goldbach_uneven(NumberStruct*){
}

NumberStruct* GoldbachPthread::find_biggest_number(){
}

int64_t GoldbachPthread::calculate_block_mapping(int64_t, int64_t, int64_t){
}

void GoldbachPthread::process_goldbach_range(PrivateData*){
}

int64_t GoldbachPthread::read_goldbach_numbers(){
}

int64_t GoldbachPthread::process_goldbach_numbers(){
}

void GoldbachPthread::print_goldbach_numbers(){
}