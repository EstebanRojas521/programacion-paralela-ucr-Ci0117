// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.
#include <stdbool.h>
#include "lamina.hpp"
#include "readTxt.hpp"
#include "writeBinary.hpp"
#include "simulacion.hpp"

void analyzeArguments();

int main(int argc, char* argv[]){
    // int numberOfThreads = 0;
    int numberOfRows = 0;
    readText* instanceTxt = new readText();
    lamina* instanceBinary = new lamina();
    writeBinary* instanceWriteBinary = new writeBinary();
    lamina_t mainStruct;
    std::string fileName = "";
    if (argc < 2) { 
        throw std::invalid_argument("Please enter a Job file.");
    }
    if(argc == 2){
        fileName = argv[1];
    }
    if(argc == 3){
        fileName = argv[2];
    }

    // Nos indica cuantas filas tiene nuestro archivo txt...
    // para iterar serialmente atraves de el
    fileName = "jobs/" + fileName;
    numberOfRows = instanceTxt->numberOfRows(fileName);
    // numberOfRows = 1; 
    for(int i = 0; i < numberOfRows; i++){
        //instanceTxt->fillTxtStruct(fileName,i);
        simulacion* simulacionDeCalor = new simulacion;
        lamina_t lamina = instanceBinary->readBinaryFile(instanceTxt->fillTxtStruct(fileName,i));
        size_t filas = lamina.rows;
        size_t columnas = lamina.columns;
        simulacionDeCalor->iniciarSimulacion(lamina, filas, columnas);
        if(i == 0)
            instanceWriteBinary->createReportTxt(lamina,true);
        else 
            instanceWriteBinary->createReportTxt(lamina,false);
        instanceWriteBinary->createReportBinary(lamina,true);
        delete simulacionDeCalor;
    }
    delete instanceTxt;
    delete instanceBinary;
    return 0;
}