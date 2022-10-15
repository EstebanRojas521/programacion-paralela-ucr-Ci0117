#include "GoldbachPthread.hpp"
#include "NumberStruct.hpp"
#include "NumberArray.hpp"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <stdint.h>
#include <unistd.h>

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

int64_t GoldbachPthread::process_even_number(NumberStruct* number_struct){
    int64_t size = number_struct->get_smaller_primes_array().get_total_numbers();
    int64_t number = (int64_t)abs((int)number_struct->get_number());
    NumberArray* sums_array = &number_struct->get_sums_array();

    for (int64_t i = 0; i < size; i++) {
        for (int64_t j = 0; j < size; j++) {
            int64_t number_i =
            number_struct->get_smaller_primes_array().get_numbers_array()[i];
            int64_t number_j =
            number_struct->get_smaller_primes_array().get_numbers_array()[j];

            if (((number_i + number_j) == number)
             && check_repeated_even(sums_array, number_i, number_j) == false) {
                number_struct->append_sums_number(number_i);
                number_struct->append_sums_number(number_j);
                number_struct->get_sums_array().increment_total_sums();
            }
        }
    }
}

int64_t GoldbachPthread::process_uneven_number(NumberStruct* number_struct){
    int64_t size = number_struct->get_smaller_primes_array().get_total_numbers();
    int64_t number = (int64_t)abs((int)number_struct->get_number());
    NumberArray* sums_array = &number_struct->get_sums_array();

    for (int64_t i = 0; i < size; i++) {
        for (int64_t j = 0; j < size; j++) {
            for (int64_t k = 0; k < size; k++) {
                int64_t number_i = number_struct->get_smaller_primes_array().
                                                  get_numbers_array()[i];
                int64_t number_j = number_struct->get_smaller_primes_array().
                                                  get_numbers_array()[j];
                int64_t number_k = number_struct->get_smaller_primes_array().
                                                  get_numbers_array()[k];

                if (((number_i + number_j + number_k) == number)
                && (check_repeated_uneven(sums_array, number_i, number_j,
                                                    number_k) == false)
                && (number_i != 0 && number_j != 0 && number_k != 0)) {
                    number_struct->append_sums_number(number_i);
                    number_struct->append_sums_number(number_j);
                    number_struct->append_sums_number(number_k);
                    number_struct->get_sums_array().increment_total_sums();
                }
            }
        }
    }
}

void GoldbachPthread::print64_t_goldbach_even(NumberStruct* number_struct){
}

void GoldbachPthread::print64_t_goldbach_uneven(NumberStruct* number_struct){
}

NumberStruct* GoldbachPthread::find_biggest_number(){
    NumberStruct* biggestNumberStruct = this->numberStructArray[0];

    for (int64_t i = 1; i < this->totalNumbers; i++) {
        int64_t biggest = (int64_t)abs((int)biggestNumberStruct->get_number());
        int64_t next_num = (int64_t)
                            abs((int)this->numberStructArray[i]->get_number());
        if (biggest < next_num) {
            biggestNumberStruct = this->numberStructArray[i];
        }
    }
    return biggestNumberStruct;
}

int64_t GoldbachPthread::calculate_block_mapping(int64_t index,
                                                 int64_t numbers,
                                                 int64_t thread_count) {
    int64_t div = numbers/thread_count;
    int64_t mod = numbers % thread_count;
    int64_t min = (index < mod) ? index : mod;
    int64_t result = (index*div) + min;
    return result;
}

void GoldbachPthread::process_goldbach_range(PrivateData*){
}

int64_t GoldbachPthread::read_goldbach_numbers(){
    int64_t error = EXIT_SUCCESS;

    FILE* input = stdin;
    long long value = 0ll;

    while (fscanf(input, "%lld", &value) == 1) {
        if (value < INT64_MAX) {
            NumberStruct* new_number = new NumberStruct();
            if (new_number) {
                new_number->set_number((int64_t)value);
                this->numberStructArray.push_back(new_number);
            } else {
                std::cerr << "Error: No se pudo crear el number_struct\n";
                error = EXIT_FAILURE;
            }
        } else {
            std::cerr << "Error: Entrada invalida";
        }
    }

    int64_t number = this->numberStructArray[0]->get_number();
    if (number) {
        this->threadCount = (int64_t)abs(number);
    } else {
        this->threadCount = sysconf(_SC_NPROCESSORS_CONF);
    }

    return error;
}

int64_t GoldbachPthread::process_goldbach_numbers(){
}

void GoldbachPthread::print_goldbach_numbers(){
}