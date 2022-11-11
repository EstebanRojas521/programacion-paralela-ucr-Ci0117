// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#include "SumGoldbachModel.hpp"
#include <cstdlib>

SumGoldbachModel::SumGoldbachModel(int64_t number,bool last)
    :number(number)
    ,last(last){}

SumGoldbachModel::~SumGoldbachModel() {}

int64_t SumGoldbachModel::isPrime(int64_t number) {
    int64_t is_prime = EXIT_SUCCESS;
    for (int64_t i = 2; i < number; i++) {
        if ((number % i) == 0) {
            is_prime = EXIT_FAILURE;
        }
    }
    return is_prime;
}

void SumGoldbachModel::calculateSmallerPrimes(NumberStruct* numberStruct) {
    int64_t struct_number = (int64_t)abs(numberStruct->number);
    for (int64_t i = 2; i < struct_number; i++) {
        if (isPrime(i) == 0) {
            numberStruct->smallerPrimes.push_back(i);
        }
    }
}

int64_t SumGoldbachModel::checkRepeatedEven(std::vector<int64_t> sumsVector,
                                                int64_t num1, int64_t num2) {
    int64_t repeated = false;
    int64_t size = sumsVector.size();
    for (int64_t i = 0; i < size; i+=2) {
        if (sumsVector[i] == num2 &&
            sumsVector[i+1] == num1) {
            repeated = true;
        }
    }
    return repeated;
}

void SumGoldbachModel::processEvenSums(NumberStruct* numberStruct) {
    int64_t size = numberStruct->smallerPrimes.size();
    int64_t number = numberStruct->number;
    int64_t abs_number = (int64_t)abs(number);
    for (int64_t i = 0; i < size; i++) {
        for (int64_t j = 0; j < size; j++) {
            int64_t number_i = numberStruct->smallerPrimes[i];
            int64_t number_j = numberStruct->smallerPrimes[j];

            if (((number_i + number_j) == abs_number)
             && checkRepeatedEven(numberStruct->results, number_i, number_j)
                                                                    == false) {
                numberStruct->results.push_back(number_i);
                numberStruct->results.push_back(number_j);
            }
        }
    }
}

int64_t SumGoldbachModel::checkRepeatedUneven(std::vector<int64_t> sumsVector,
                                     int64_t num1, int64_t num2, int64_t num3) {
    int64_t repeated = false;
    int64_t size = sumsVector.size();
    for (int64_t i = 0; i < size; i+=3) {
        int64_t number_i = sumsVector[i];
        int64_t number_i_plus = sumsVector[i+1];
        int64_t number_i_plus_plus = sumsVector[i+2];

        if ((number_i == num1 && number_i_plus == num3
        && number_i_plus_plus == num2)
        || (number_i == num2 && number_i_plus == num3
        && number_i_plus_plus == num1)
        || (number_i == num2 && number_i_plus == num1
        && number_i_plus_plus == num3)
        || (number_i == num3 && number_i_plus == num1
        && number_i_plus_plus == num2)
        || (number_i == num3 && number_i_plus ==
        num2 && number_i_plus_plus == num1)) {
            repeated = true;
        }
    }
    return repeated;
}


void SumGoldbachModel::processUnevenSums(NumberStruct* numberStruct) {
    int64_t size = numberStruct->smallerPrimes.size();
    int64_t number = numberStruct->number;
    int64_t abs_number = (int64_t)abs(number);
    for (int64_t i = 0; i < size; i++) {
        for (int64_t j = 0; j < size; j++) {
            for (int64_t k = 0; k < size; k++) {
                int64_t number_i = numberStruct->smallerPrimes[i];
                int64_t number_j = numberStruct->smallerPrimes[j];
                int64_t number_k = numberStruct->smallerPrimes[k];

                if (((number_i + number_j + number_k) == abs_number)
                && (checkRepeatedUneven(numberStruct->results, number_i,
                                        number_j, number_k) == false)
                && (number_i != 0 && number_j != 0 && number_k != 0)) {
                    numberStruct->results.push_back(number_i);
                    numberStruct->results.push_back(number_j);
                    numberStruct->results.push_back(number_k);
                }
            }
        }
    }
}

GoldbachStruct SumGoldbachModel::processGoldbachNumber(NumberStruct* numberStruct) {
     GoldbachStruct answer;
    int64_t absNumber = (int64_t)abs(numberStruct->number);
    if (absNumber > 5) {
        // numberStruct->results = results;
        calculateSmallerPrimes(numberStruct);

        if (absNumber % 2 == 0) {
            processEvenSums(numberStruct);
        } else {
            processUnevenSums(numberStruct);
        }
    } else if (absNumber == 4) {
        numberStruct->results.push_back(2);
        numberStruct->results.push_back(2);
    }
    answer.number = numberStruct->number;
    answer.resultsVector = numberStruct->results;
    return answer;
}


int SumGoldbachModel::run() {
    //std::vector<NumberStruct> numberStruct;

    GoldbachStruct answer;
    // Creating vector of numbers
    
    // lleno vector -> calculo golbach
    //int size = httpPackage.numerosIngresados.size();
    //int64_t number = httpPackage.numerosIngresados[i];
    // Se crea numberStruct
    NumberStruct* numberStruct = new NumberStruct();
    // Se asigna numero ingresado al numberStruct
    numberStruct->number = this->number;
    // Se procesan las sumas de goldbach
    this->produce(this->processGoldbachNumber(numberStruct));
    //std::cout<<numberStruct->number<<std::endl;
    // condicion de parada
    if(last == true){
        this->produce(GoldbachStruct());
    }
    answer.resultsVector = numberStruct->results;
    answer.number = number;
    return 0;
}


void SumGoldbachModel::goldbach_print(struct NumberStruct* numberStruct,
                                             HttpResponse& httpResponse) {
    int64_t absNumber = (int64_t)abs(numberStruct->number);
    if ((absNumber%2) == 0) {
        print_even(numberStruct, httpResponse);
    } else {
        print_odd(numberStruct, httpResponse);
    }
    httpResponse.body() << "<h1>     </h1>\n";
}


void SumGoldbachModel::print_even(struct NumberStruct* numberStruct,
                                        HttpResponse& httpResponse) {
    int64_t minusOne = -1;
    if (numberStruct->number != minusOne) {
        httpResponse.body() << numberStruct->number << ": "
        << numberStruct->results.size()/2  << " sums ";
        if (numberStruct->number < 0) {
            for (size_t j = 0; j < numberStruct->results.size() ; j+=2) {
                int64_t results_j = numberStruct->results[j];
                int64_t results_j_plus = numberStruct->results[j+1];

                if ((j == 0) && (numberStruct->results.size()  != 1)) {
                    httpResponse.body() << results_j << "+"
                                        << results_j_plus;
                } else {
                    if ((j == (numberStruct->results.size() -1))) {
                        if (numberStruct->results.size()  == 1) {
                            httpResponse.body() << results_j << "+"
                                                << results_j_plus;
                        } else {
                            httpResponse.body() << results_j << "+"
                                                << results_j_plus;
                        }
                    } else {
                        httpResponse.body() << results_j << "+"
                                            << results_j_plus;
                    }
                }
                if (j+1 < numberStruct->results.size()-1) {
                    httpResponse.body() << ", ";
                }
            }
        }
    } else {
        httpResponse.body() << numberStruct->number << ": NA ";
    }
    httpResponse.body() << "\n";
}


void SumGoldbachModel::print_odd(struct NumberStruct* numberStruct,
                                        HttpResponse& httpResponse) {
    if (numberStruct->number != -1) {
        httpResponse.body() << numberStruct->number << ": "
        << numberStruct->results.size()/3 << " sums";
        if (numberStruct->number < 0) {
            httpResponse.body() << ": ";
            for (size_t j = 0; j < numberStruct->results.size(); j+=3) {
                int64_t results_j = numberStruct->results[j];
                int64_t results_j_plus = numberStruct->results[j+1];
                int64_t results_j_plus_plus = numberStruct->results[j+2];

                if ((j == 0) && (numberStruct->results.size() != 1)) {
                    httpResponse.body() << results_j << "+"
                                        << results_j_plus << "+"
                                        << results_j_plus_plus;
                } else {
                    if ((j == (numberStruct->results.size()-1))) {
                        if (numberStruct->results.size() == 1) {
                            httpResponse.body() << results_j << "+"
                                                << results_j_plus << "+"
                                                << results_j_plus_plus;
                        } else {
                            httpResponse.body() << results_j << "+"
                                                << results_j_plus << "+"
                                                << results_j_plus_plus;
                        }
                    } else {
                        httpResponse.body() << results_j << "+"
                                            << results_j_plus << "+"
                                            << results_j_plus_plus;
                    }
                }
                if (j+2 < numberStruct->results.size()-1) {
                    httpResponse.body() << ", ";
                }
            }
        }
    } else {
        httpResponse.body() << numberStruct->number << ": NA";
    }
    httpResponse.body() << "\n";
}
