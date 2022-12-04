// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#include "readTxt.hpp"



int main(int argc, char* argv[]){
    // int numberOfThreads = 0;
    int numberOfRows = 0;
    readText* instanceTxt = new readText();
    std::string fileName = "";
    if (argc < 2) { 
        throw std::invalid_argument("Please enter a Job file.");
    }
    if(argc == 2){
        fileName = argv[1];
        //numberOfThreads = 10;
    }
    if(argc == 3){
        fileName = argv[2];
        //numberOfThreads = std::stoi(argv[3]);
    }
    // Nos indica cuantas filas tiene nuestro archivo txt...
    // para iterar serialmente atraves de el
    numberOfRows = instanceTxt->numberOfRows(fileName);

    // numberOfRows = 1;
    for(int i = 0;i<numberOfRows;i++){
        instanceTxt->fillTxtStruct(fileName,i);
        // Leemos binarios
        // Calculamos 
        // Reportamos
    }
    // end for

    return 0;
}