#include "NumberArray.hpp"
#include <stdint.h>

NumberArray::NumberArray() {
    this->totalNumbers = 0;
    this->totalSums = 0;
}

NumberArray::~NumberArray(){ }

int64_t NumberArray::get_total_numbers() {
    return this->totalNumbers;
}

int64_t NumberArray::get_total_sums() {
    return this->totalSums;
}

void NumberArray::set_total_sums(int64_t total_sums) {
    this->totalSums = total_sums;
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