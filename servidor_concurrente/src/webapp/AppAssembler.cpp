// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#include <string>
#include "AppAssembler.hpp"

AppAssembler::AppAssembler(HttpPackage& package)
    :package(package) {
}

int AppAssembler::run() {
    this->consumeForever();
    return 0;
}

void AppAssembler::consume(GoldbachStruct data) {
    data = data;

    // //std::cout<<"Im in AppAssembler"<<std::endl;
    // std::cout<<"Number: "<<data.number<<std::endl;
    // if(data.number%2 == 0){
    //     std::cout<<"Sums: "<<data.resultsVector.size()/2<<std::endl;
    // }
    // for(int i = 0;i<data.resultsVector.size();i++){
    //    // std::cout<<": "<<data.number<<std::endl;
    // }
    // //aca imprimo resultados

    // aca creamos HTML para enviarlo al sender

    if (data.first == true) {
        // std::cout<<"GOT TO APP"<<std::endl;
        package.httpResponse.setHeader("Server", "AttoServer v1.0");
        package.httpResponse.setHeader("Content-type",
        "text/html; charset=ascii");
        std::string title = "Sums of Goldbach of ";
        int numbers_size =  package.numerosIngresados.size();
        for (int i=0; i < numbers_size; i++) {
            std::cout<< this->package.numerosIngresados[i] << std::endl;
            title += std::to_string(this->package.numerosIngresados[i]);
            if (i+1 != numbers_size) {
                title += ',';
            }
        }

        package.httpResponse.body() << "<!DOCTYPE html>\n"
        << "  <html lang=\"en\">\n"
        << "  <meta charset=\"ascii\"/>\n"
        << "  <title>" << title << "</title>\n"
        << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
        << "  <h1>" << title << "</h1>\n";
    }
    this->goldbach_print(data);
    if (data.last == true) {
        // llamamos a sender
        package.httpResponse.body()
        << "  <hr><p><a href=\"/\">Back</a></p>\n"
        << "</html>\n";
        // this->produceASBM(GoldbachStruct());

        // no hice sender:(
        std::cout <<"Im on app assembler sender" <<std::endl;
        this->produce(GoldbachStruct());
        this->package.httpResponse.send();
    }
}

void AppAssembler::goldbach_print(GoldbachStruct data) {
    int64_t absNumber = (int64_t)abs(data.number);
    if ((absNumber%2) == 0) {
        print_even(data);
    } else {
        print_odd(data);
    }
    package.httpResponse.body() << "<h1>     </h1>\n";
}

void AppAssembler::print_even(GoldbachStruct data) {
    int64_t minusOne = -1;
    if (data.number != minusOne) {
        package.httpResponse.body() << data.number << ": "
        << data.resultsVector.size()/2  << " sums ";
        if (data.number < 0) {
            for (size_t j = 0; j < data.resultsVector.size() ; j+=2) {
                int64_t results_j = data.resultsVector[j];
                int64_t results_j_plus = data.resultsVector[j+1];

                if ((j == 0) && (data.resultsVector.size()  != 1)) {
                    package.httpResponse.body() << results_j << "+"
                                        << results_j_plus;
                } else {
                    if ((j == (data.resultsVector.size() -1))) {
                        if (data.resultsVector.size()  == 1) {
                            package.httpResponse.body() << results_j << "+"
                                                << results_j_plus;
                        } else {
                            package.httpResponse.body() << results_j << "+"
                                                << results_j_plus;
                        }
                    } else {
                        package.httpResponse.body() << results_j << "+"
                                            << results_j_plus;
                    }
                }
                if (j+1 < data.resultsVector.size()-1) {
                    package.httpResponse.body() << ", ";
                }
            }
        }
    } else {
        package.httpResponse.body() << data.number << ": NA ";
    }
    package.httpResponse.body() << "\n";
}


void AppAssembler::print_odd(GoldbachStruct data) {
    if (data.number != -1) {
        package.httpResponse.body() << data.number << ": "
        << data.resultsVector.size()/3 << " sums";
        if (data.number < 0) {
            package.httpResponse.body() << ": ";
            for (size_t j = 0; j < data.resultsVector.size(); j+=3) {
                int64_t results_j = data.resultsVector[j];
                int64_t results_j_plus = data.resultsVector[j+1];
                int64_t results_j_plus_plus = data.resultsVector[j+2];

                if ((j == 0) && (data.resultsVector.size() != 1)) {
                    package.httpResponse.body() << results_j << "+"
                                        << results_j_plus << "+"
                                        << results_j_plus_plus;
                } else {
                    if ((j == (data.resultsVector.size()-1))) {
                        if (data.resultsVector.size() == 1) {
                            package.httpResponse.body() << results_j << "+"
                                                << results_j_plus << "+"
                                                << results_j_plus_plus;
                        } else {
                            package.httpResponse.body() << results_j << "+"
                                                << results_j_plus << "+"
                                                << results_j_plus_plus;
                        }
                    } else {
                        package.httpResponse.body() << results_j << "+"
                                            << results_j_plus << "+"
                                            << results_j_plus_plus;
                    }
                }
                if (j+2 < data.resultsVector.size()-1) {
                    package.httpResponse.body() << ", ";
                }
            }
        }
    } else {
        package.httpResponse.body() << data.number << ": NA";
    }
    package.httpResponse.body() << "\n";
}

