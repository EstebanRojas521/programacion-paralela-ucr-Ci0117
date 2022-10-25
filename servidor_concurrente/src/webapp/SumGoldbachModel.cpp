#include "SumGoldbachModel.hpp"
#include <cstdlib>

SumGoldbachModel::SumGoldbachModel() { }

SumGoldbachModel::~SumGoldbachModel() { }

int64_t SumGoldbachModel::is_prime(int64_t number){
    int64_t is_prime = EXIT_SUCCESS;

    for (int64_t i = 2; i < number; i++){
        if ((number % i) == 0) {
            is_prime = EXIT_FAILURE;
        }
    }
    return is_prime;
}

void SumGoldbachModel::calculate_smaller_primes(NumberStruct* numberStruct){
    int64_t struct_number = (int64_t)abs((int)numberStruct->number);
    for (int64_t i = 2; i < struct_number; i++) {
        if (is_prime(i) == 0) {
            numberStruct->smallerPrimes.push_back(i);
            numberStruct->totalPrimes++;
        }
    }
}

int64_t SumGoldbachModel::check_repeated_even(std::vector<size_t>& sumsVector,
                                                    int64_t num1, int64_t num2){
    int64_t repeated = false;
    int64_t size = sumsVector.size();
    for (int64_t i = 0; i < size; i+=2) {
        if (sumsVector[i] == (size_t)num2 &&
            sumsVector[i+1] == (size_t)num1) {
            repeated = true;
        }
    }
    return repeated;
}

void SumGoldbachModel::processEvenSums(NumberStruct* numberStruct, std::vector<size_t>& sumsVector){
    int64_t size = numberStruct->totalPrimes;
    int64_t number = numberStruct->number;
    for (int64_t i = 0; i < size; i++) {
        for (int64_t j = 0; j < size; j++) {
            int64_t number_i = numberStruct->smallerPrimes[i];
            int64_t number_j = numberStruct->smallerPrimes[j];

            if (((number_i + number_j) == number)
             && check_repeated_even(sumsVector, number_i, number_j) == false) {
                sumsVector.push_back(number_i);
                sumsVector.push_back(number_j);
            }
        }
    }
}

int64_t SumGoldbachModel::check_repeated_uneven(
    std::vector<size_t>& sumsVector, int64_t num1, int64_t num2, int64_t num3){
    int64_t repeated = false;
    int64_t size = sumsVector.size();
    for (int64_t i = 0; i < size; i+=3) {
        int64_t number_i = sumsVector[i];
        int64_t number_i_plus = sumsVector[i+1];
        int64_t number_i_plus_plus = sumsVector[i+2];

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
    return repeated;
}


void SumGoldbachModel::processUnevenSums(NumberStruct* numberStruct, std::vector<size_t>& sumsVector){
    int64_t size = numberStruct->totalPrimes;
    int64_t number = numberStruct->number;
    for (int64_t i = 0; i < size; i++) {
        for (int64_t j = 0; j < size; j++) {
            for (int64_t k = 0; k < size; k++) {
                int64_t number_i = numberStruct->smallerPrimes[i];
                int64_t number_j = numberStruct->smallerPrimes[j];
                int64_t number_k = numberStruct->smallerPrimes[k];

                if (((number_i + number_j + number_k) == number)
                && (check_repeated_uneven(sumsVector, number_i,
                                        number_j, number_k) == false)
                && (number_i != 0 && number_j != 0 && number_k != 0)) {
                    sumsVector.push_back(number_i);
                    sumsVector.push_back(number_j);
                    sumsVector.push_back(number_k);
                }
            }  
        }
    }
}

void SumGoldbachModel::processGoldbachNumber(size_t number, std::vector<size_t>& sumsVector) {
    int64_t absNumber = (int64_t)abs((int)number);
    if(absNumber > 5) {
        NumberStruct* numberStruct = new NumberStruct();
        numberStruct->number = absNumber;
        calculate_smaller_primes(numberStruct);
        if (absNumber % 2 == 0) {
            processEvenSums(numberStruct, sumsVector);
        } else {
            processUnevenSums(numberStruct, sumsVector);
        }
        delete numberStruct;
    } else if (absNumber == 4) {
        sumsVector.push_back(2);
        sumsVector.push_back(2);
    }
}