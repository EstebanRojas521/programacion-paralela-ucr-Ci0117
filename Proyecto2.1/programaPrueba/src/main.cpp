// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#include "../../src/lamina.hpp"
//#include "../../output/plate001-4.bin"
//#include "../../jobs"
#include "comparador.h"

#include <string>

int main(int argc, char* argv[]){

    if (argc != 4) {
        std::string error = "";
        error += "usage: bin/programaPrueba ../jobs/jobxxx/jobxxx.bin";
        error += " ../jobs/jobxxx/jobxxx.bin epsilon";
        throw std::invalid_argument(error);
    }

    comparador* miComparador = new comparador;

    lamina_t laminaA;
    txtData txtDataA;
    txtDataA.plateName = argv[1];
    lamina_t laminaB;
    txtData txtDataB;
    txtDataB.plateName = argv[2];
    // Buscamos nuestra plate en la carpeta de plates suministrada 
    // por el profe, y la comparamos con el plate que obtuvimos
    txtDataA.plateName = "../output/"+txtDataA.plateName;
    txtDataB.plateName = "../jobs/" + txtDataB.plateName;
    laminaA = miComparador->readBinaryFile(txtDataA);
    laminaB = miComparador->readBinaryFile(txtDataB);
    //std::cout << txtDataA.plateName << std::endl;
    laminaA.epsilon = laminaB.epsilon = std::stod(argv[3]);

    bool iguales = miComparador->compare(laminaA, laminaB);
    if (iguales == true) {
        std::cout << "\nLas matrices son iguales\n"<< std::endl;
    } else {
        std::cout << "\nLas matrices son diferentes\n"<<std::endl;
    }
    delete miComparador;
    return 0;
}