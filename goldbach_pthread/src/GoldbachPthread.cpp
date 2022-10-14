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

int64_t GoldbachPthread::check_repeated_even(
    NumberArray* number_array, int64_t num1, int64_t num2){
    int64_t repeated = false;
    if (number_array->get_total_numbers() == 0) {
    } else {
        int64_t size = number_array->get_total_numbers();
        std::vector<int64_t> numbers_array =
                            number_array->get_numbers_array();
        for (int64_t i = 0; i < size; i+=2) {
            if (numbers_array[i] == num2 &&
                numbers_array[i+1] == num1) {
                    repeated = true;
                }
        }
    }
    return repeated;
}

int64_t GoldbachPthread::check_repeated_uneven(
    NumberArray* number_array, int64_t num1, int64_t num2, int64_t num3){
    int64_t repeated = false;
    if (number_array->get_total_numbers() == 0) {
    } else {
        int64_t size = number_array->get_total_numbers();
        std::vector<int64_t> numbers_array =
                            number_array->get_numbers_array();
        for (int64_t i = 0; i < size; i+=3) {
            int64_t number_i = numbers_array[i];
            int64_t number_i_plus = numbers_array[i+1];
            int64_t number_i_plus_plus = numbers_array[i+2];

            if ((number_i == num1 && number_i_plus == num3 && number_i_plus_plus
                                                                    == num2)
            || (number_i == num2 && number_i_plus == num3 && number_i_plus_plus
                                                                    == num1)
            || (number_i == num2 && number_i_plus == num1 && number_i_plus_plus
                                                                    == num3)
            || (number_i == num3 && number_i_plus == num1 && number_i_plus_plus
                                                                    == num2)
            || (number_i == num3 && number_i_plus == num2 && number_i_plus_plus
                                                                    == num1)) {
                repeated = true;
            }
        }
    }
    return repeated;
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