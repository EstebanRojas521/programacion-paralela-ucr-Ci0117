#ifndef NUMBER_ARRAY_HPP
#define NUMBER_ARRAY_HPP

#include <vector>
#include <stdint.h>

class number_array{

    int64_t total_numbers;
    int64_t total_sums;
    std::vector<int64_t> nums_array;

    public:
    
    number_array();
    ~number_array();
};

#endif
