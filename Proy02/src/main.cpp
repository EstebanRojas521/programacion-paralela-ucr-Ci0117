// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#include "lamina.hpp"
#include "readTxt.hpp"
#include "simulacion.hpp"

int main(int argc, char* argv[]){
    // int numberOfThreads = 0;
    int numberOfRows = 0;
    readText* instanceTxt = new readText();
    lamina* instanceBinary = new lamina();
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
    for(int i = 0; i < numberOfRows; i++){
        simulacion* simulacionDeCalor = new simulacion;
        //instanceTxt->fillTxtStruct(fileName,i);
        lamina_t lamina = instanceBinary->readBinaryFile(instanceTxt->fillTxtStruct(fileName,i));
        size_t filas = lamina.rows;
        size_t columnas = lamina.columns;
        simulacionDeCalor->iniciarSimulacion(lamina, filas, columnas);
        // Calculamos 
        // Reportamos
        delete simulacionDeCalor;
    }

    delete instanceTxt;
    delete instanceBinary;
    return 0;
}