#ifndef NUMBER_ARRAY_HPP
#define NUMBER_ARRAY_HPP

#include <vector>
#include <stdint.h>

class NumberArray{

    int64_t totalNumbers;
    int64_t totalSums;
    std::vector<int64_t> numbersArray;

    public:
    
    NumberArray();
    ~NumberArray();

    int64_t get_total_numbers();
    int64_t get_total_sums();
    std::vector<int64_t> get_numbers_array();

    void increment_total_sums();

    void append_number(int64_t number);
};

#endif
