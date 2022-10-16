#ifndef SUMGOLDBACHMODEL
#define SUMGOLDBACHMODEL
#include <vector>
#include <cstdlib>

struct NumberStruct{
    int64_t number;
    std::vector<int64_t> smallerPrimes;
    int64_t totalPrimes;
};

class SumGoldbachModel {

    public:

    SumGoldbachModel();
    ~SumGoldbachModel();

    int64_t is_prime(int64_t);
    void calculate_smaller_primes(NumberStruct*);

    int64_t check_repeated_even(std::vector<size_t>&, int64_t, int64_t);
    void processEvenSums(NumberStruct*, std::vector<size_t>&);

    int64_t check_repeated_uneven(std::vector<size_t>&, int64_t, int64_t, int64_t);
    void processUnevenSums(NumberStruct*, std::vector<size_t>&);

    void processGoldbachNumber(size_t, std::vector<size_t>&);
};

#endif