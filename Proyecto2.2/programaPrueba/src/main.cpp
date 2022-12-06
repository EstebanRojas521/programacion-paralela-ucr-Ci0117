// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#include "../../src/lamina.hpp"
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
    laminaA = miComparador->readBinaryFile(txtDataA);
    laminaB = miComparador->readBinaryFile(txtDataB);

    laminaA.epsilon = laminaB.epsilon = std::stod(argv[3]);

    bool iguales = miComparador->compare(laminaA, laminaB);

    if (iguales == true) {
        std::cout << "\nLas matrices son iguales\n";
    } else {
        std::cout << "\nLas matrices son diferentes\n";
    }

    delete miComparador;
    return 0;
}