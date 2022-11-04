// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.


#include "SumGoldbachModel.hpp"
#include <cstdlib>

SumGoldbachModel::SumGoldbachModel() {}

SumGoldbachModel::~SumGoldbachModel() {}

int64_t SumGoldbachModel::is_prime(int64_t number) {
    int64_t is_prime = EXIT_SUCCESS;
    for (int64_t i = 2; i < number; i++) {
        if ((number % i) == 0) {
            is_prime = EXIT_FAILURE;
        }
    }
    return is_prime;
}

void SumGoldbachModel::calculate_smaller_primes(NumberStruct* numberStruct) {
    int64_t struct_number = (int64_t)abs((int)numberStruct->number);
    for (int64_t i = 2; i < struct_number; i++) {
        if (is_prime(i) == 0) {
            numberStruct->smallerPrimes.push_back(i);
            numberStruct->totalPrimes++;
        }
    }
}

int64_t SumGoldbachModel::check_repeated_even(std::vector<int64_t> sumsVector,
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
    int64_t size = numberStruct->totalPrimes;
    int64_t number = numberStruct->number;
    for (int64_t i = 0; i < size; i++) {
        for (int64_t j = 0; j < size; j++) {
            int64_t number_i = numberStruct->smallerPrimes[i];
            int64_t number_j = numberStruct->smallerPrimes[j];

            if (((number_i + number_j) == number)
             && check_repeated_even(numberStruct->results, number_i, number_j) == false) {
                
                numberStruct->results.push_back(number_i);
                numberStruct->results.push_back(number_j);
            }
        }
    }
}

int64_t SumGoldbachModel::check_repeated_uneven(std::vector<int64_t> sumsVector
, int64_t num1, int64_t num2, int64_t num3) {
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


void SumGoldbachModel::processUnevenSums(NumberStruct*numberStruct) {
    int64_t size = numberStruct->totalPrimes;
    int64_t number = numberStruct->number;
    for (int64_t i = 0; i < size; i++) {
        for (int64_t j = 0; j < size; j++) {
            for (int64_t k = 0; k < size; k++) {
                int64_t number_i = numberStruct->smallerPrimes[i];
                int64_t number_j = numberStruct->smallerPrimes[j];
                int64_t number_k = numberStruct->smallerPrimes[k];

                if (((number_i + number_j + number_k) == number)
                && (check_repeated_uneven(numberStruct->results, number_i,
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

void SumGoldbachModel::serveGolbach(int start, int finish,
HttpPackage& httpPackage,std::string URI) {
    std::vector<NumberStruct> numberStruct;
    //aca proceso el URL -> creo vector 
    std::cout<<"Start: "<< start <<std::endl;
    std::cout<<"Finish: "<< finish <<std::endl;

    //xxx

    std::cout<<"URI: "<< httpPackage.httpRequest.getURI() <<std::endl;
    this->createVectorOfNumbers
    (start, finish, URI,
    httpPackage.numerosIngresados);


    //xxx
    httpPackage.httpResponse.setHeader
  ("Server", "AttoServer v1.0");
  httpPackage.httpResponse.setHeader
  ("Content-type", "text/html; charset=ascii");

  std::string title = "Sums of Goldbach of ";
  int numbers_size = httpPackage.numerosIngresados.size();
  for (int i=0; i < numbers_size; i++) {
    std::cout<<"Number: "<<httpPackage.numerosIngresados[i]<<std::endl;
    title += std::to_string(httpPackage.numerosIngresados[i]);
    if (i+1 == numbers_size) {
      break;
    }
    title += ',';
  }
  httpPackage.httpResponse.body() << "<!DOCTYPE html>\n"
  << "  <html lang=\"en\">\n"
  << "  <meta charset=\"ascii\"/>\n"
  << "  <title>" << title << "</title>\n"
  << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
  << "  <h1>" << title << "</h1>\n";






    //lleno vector -> calculo golbach
    int size = httpPackage.numerosIngresados.size();
    
    for(int i = 0;i<size;i++){
        int64_t absNumber = (int64_t)abs
        ((int)httpPackage.numerosIngresados[i]);

        //positivo
        //::vector<int64_t> results;  
        NumberStruct* numberStruct = new NumberStruct();
        if (absNumber > 5) {
            numberStruct->number =  absNumber;
             std::cout<<"Struct number: "<< numberStruct->number <<std::endl;
            //numberStruct->results = results;
            calculate_smaller_primes(numberStruct);
            if (absNumber % 2 == 0) {
                processEvenSums(numberStruct);
            } else {
                processUnevenSums(numberStruct);
            }
        } else if (absNumber == 4) {
            numberStruct->results.push_back(2);
            numberStruct->results.push_back(2);
        }
        //empezamos a crear body
        //numberStruct->number =  ((int)httpPackage.numerosIngresados[i]);
            this->goldbach_print(numberStruct, httpPackage.httpResponse);
        //terminamos de crear body
            //results.clear();
            delete numberStruct;
        //vamos con siguiente numero
    }



    httpPackage.httpResponse.body()
    << "  <hr><p><a href=\"/\">Back</a></p>\n"
    << "</html>\n";

    //Imprimo, llamo vector? no tengo idea
    //this->SumGoldbachModel.validRequest(httpPackage);
    
}



void SumGoldbachModel::createVectorOfNumbers(int start
, int finish, const std::string URI
, std::vector<int64_t>& numbers) {
  bool out_of_limit  = false;
  std::string number = "";
  for (int i = start + 1; i <= finish && !out_of_limit ; i++) {
    // std::cout<< start << std::endl;
    if (URI[i] != '+' && i != finish) {
      number += URI[i];
    } else {
      int64_t converted_number;
      if (i != finish) {
        out_of_limit = convertStringToInt(number, converted_number);
        if (!out_of_limit) {
          numbers.push_back(converted_number);
          number = "";
        }
      } else { 
        number += URI[i];
        out_of_limit  = convertStringToInt(number, converted_number);
        if (!out_of_limit) {
        numbers.push_back(converted_number);
        }
      }
    }

  }
}

bool SumGoldbachModel::convertStringToInt(std::string& number
, int64_t& converted_number) {
  bool out_of_limit = false;
  try {
    converted_number = std::stoll(number);
  } catch (const std::out_of_range& out_of_range) {
    out_of_limit = true;
  }
  return out_of_limit;
}






void SumGoldbachModel::goldbach_print(struct NumberStruct* numberStruct, HttpResponse& httpResponse) {
  int64_t absNumber = (int64_t)abs
        ((int)numberStruct->number);
  //for (size_t i = 0; i < golbachElements.size(); i++) {
      if ((absNumber%2) == 0) {

        print_even(numberStruct, httpResponse);
      } else {
        print_odd(numberStruct, httpResponse);
      }
      httpResponse.body() << "<h1>     </h1>\n";
  //}
}


void SumGoldbachModel::print_even(struct NumberStruct* numberStruct,
 HttpResponse& httpResponse) {
   int64_t count = 0;
  int64_t minusOne = -1;
  std::cout<< "EVEN" <<std::endl;
  if (numberStruct->number != minusOne) {
      httpResponse.body() << numberStruct->number << ": "
      << numberStruct->results.size()  << " sums ";
      if (numberStruct->number < 0) {
        for (size_t j = 0; j < numberStruct->results.size() ; j++) {
          if ((j == 0) && (numberStruct->results.size()  != 1)) {
            httpResponse.body()
            << numberStruct->results[count] << "+"
            << numberStruct->results[count+1];
            } else {
            if ((j == (numberStruct->results.size() -1))) {
              if (numberStruct->results.size()  == 1) {
                httpResponse.body()
                << numberStruct->results[count] << "+"
                << numberStruct->results[count+1];
              } else {
                httpResponse.body()
                << numberStruct->results[count] << "+"
                << numberStruct->results[count+1];
              }
            } else {
              httpResponse.body()
              << numberStruct->results[count] << "+"
              << numberStruct->results[count+1];
            }
          }
          count += 2;
          if ( j < numberStruct->results.size() -1 ) {
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
 int64_t count = 0;
  int64_t minusOne = -1;
  if (numberStruct->number != -1) {
        httpResponse.body() << numberStruct->number << ": "
        << numberStruct->results.size() << " sums";
        if (numberStruct->number < 0) {
          httpResponse.body() << ": ";
          for (size_t j = 0; j < numberStruct->results.size(); j++) {
            if ((j == 0) && (numberStruct->results.size() != 1)) {
              httpResponse.body()
              << numberStruct->results[count] << "+"
              << numberStruct->results[(count)+1] << "+"
              << numberStruct->results[(count)+2];
            } else {
              if ((j == (numberStruct->results.size()-1))) {
                if (numberStruct->results.size() == 1) {
                  httpResponse.body()
                  << numberStruct->results[count] << "+"
                  << numberStruct->results[(count)+1] << "+"
                  << numberStruct->results[(count)+2];
                } else {
                  httpResponse.body()
                  << numberStruct->results[count] << "+"
                  << numberStruct->results[(count)+1] << "+"
                  << numberStruct->results[(count)+2];
                }
              } else {
                httpResponse.body()
                << numberStruct->results[count] << "+"
                << numberStruct->results[(count)+1] << "+"
                << numberStruct->results[(count)+2];
              }
            }
            count += 3;
            if ( j < numberStruct->results.size()-1 ) {
              httpResponse.body() << ", ";
            }
          }
        }
      } else {
        httpResponse.body() << numberStruct->number << ": NA";
      }
      httpResponse.body() << "\n";
}
