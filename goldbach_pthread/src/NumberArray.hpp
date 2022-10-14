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
};

#endif
