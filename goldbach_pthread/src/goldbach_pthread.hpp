#ifndef GOLDBACH_PHTHREAD_HPP
#define GOLDBACH_PHTHREAD_HPP

#include "number_struct.hpp"
#include "number_array.hpp"
#include <vector>
#include <stdint.h>

struct private_data{
    goldbach_pthread* goldbach_pthread;
    int64_t start;
    int64_t finish;
};

class goldbach_pthread{

    int64_t thread_count;
    int64_t total_sums;
    int64_t total_numbers;

    number_struct* biggest_number_struct;
    std::vector<number_struct*> number_struct_array;
    
    public:
    goldbach_pthread();
    ~goldbach_pthread();

    int64_t is_prime(int64_t);
    int64_t calculate_smaller_primes(number_struct*);

    int64_t check_repeated_even(number_array*, int64_t, int64_t);
    int64_t check_repeated_uneven(number_array*, int64_t, int64_t, int64_t);

    int64_t process_even_number(number_struct*);
    int64_t process_uneven_number(number_struct*);

    void print64_t_goldbach_even(number_struct*);
    void print64_t_goldbach_uneven(number_struct*);

    number_struct* find_biggest_number();
    int64_t calculate_block_mapping(int64_t, int64_t, int64_t);

    int64_t read_goldbach_numbers();
    int64_t process_goldbach_numbers();
    void print_goldbach_numbers();

};

#endif
