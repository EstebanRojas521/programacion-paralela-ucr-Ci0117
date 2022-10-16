#ifndef NUMBER_ARRAY_HPP
#define NUMBER_ARRAY_HPP

#include <vector>
#include <stdint.h>

class NumberArray{
    
    public:

    int64_t totalNumbers;
    int64_t totalSums;
    std::vector<int64_t> numbersArray;
    
    NumberArray();
    ~NumberArray();

    int64_t get_total_numbers();
    int64_t get_total_sums();
    void set_total_sums(int64_t);
    std::vector<int64_t> get_numbers_array();

    void increment_total_sums();

    void append_number(int64_t number);
};

#endif
