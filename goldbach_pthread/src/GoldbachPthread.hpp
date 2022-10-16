#ifndef GOLDBACH_PTHREAD_HPP
#define GOLDBACH_PTHREAD_HPP

#include "NumberStruct.hpp"
#include "NumberArray.hpp"
#include <vector>
#include <stdint.h>



class GoldbachPthread{

    int64_t threadCount;
    int64_t totalSums;
    int64_t totalNumbers;

    NumberStruct* biggestNumberStruct;
    std::vector<NumberStruct*> numberStructArray;
    
    public:
    GoldbachPthread();
    ~GoldbachPthread();

    int64_t is_prime(int64_t);
    int64_t calculate_smaller_primes(NumberStruct*);

    int64_t check_repeated_even(NumberArray*, int64_t, int64_t);
    int64_t check_repeated_uneven(NumberArray*, int64_t, int64_t, int64_t);

    int64_t process_even_number(NumberStruct*, NumberStruct*);
    int64_t process_uneven_number(NumberStruct*, NumberStruct*);

    void print64_t_goldbach_even(NumberStruct*);
    void print64_t_goldbach_uneven(NumberStruct*);

    NumberStruct* find_biggest_number();
    int64_t calculate_block_mapping(int64_t, int64_t, int64_t);
    void calculate_total_sums();

    int64_t read_goldbach_numbers();
    int64_t process_goldbach_numbers();
    void print_goldbach_numbers();

};


#endif
