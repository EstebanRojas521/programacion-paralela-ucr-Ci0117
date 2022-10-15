#include "NumberArray.hpp"
#include <stdint.h>

int64_t NumberArray::get_total_numbers() {
    return this->totalNumbers;
}

int64_t NumberArray::get_total_sums() {
    return this->totalSums;
}

std::vector<int64_t> NumberArray::get_numbers_array() {
    return this->numbersArray;
}

void NumberArray::increment_total_sums() {
    this->totalSums++;
}

void NumberArray::append_number(int64_t number) {
    this->numbersArray.push_back(number);
    this->totalNumbers++;
}