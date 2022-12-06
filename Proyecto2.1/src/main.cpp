// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.
#include <omp.h>
#include <stdbool.h>
#include <thread>
#include "lamina.hpp"
#include "readTxt.hpp"
#include "writeBinary.hpp"
#include "simulacion.hpp"

/**
 * @brief Method used to read arguments when executing 
 * @param argc argument count
 * @param argv argument vector
 * @param fileName name of file to read
 * @param threads amount of threads specified, if not, number of cores
 */
void analyzeArguments(int argc, char* argv[], std::string &fileName,
                                                        int &threads);

int main(int argc, char* argv[]) {
    // Creamos instancias
    readText* instanceTxt = new readText();
    lamina* instanceBinary = new lamina();
    writeBinary* instanceWriteBinary = new writeBinary();
    // Numero de hilo
    int numberOfThreads = 0;
    int numberOfRows = 0;
    std::string fileName = "";
    std::vector<lamina_t> laminas;
    // Analizamos los argumentos en linea de comandos
    analyzeArguments(argc, argv, fileName, numberOfThreads);
    // Nos indica cuantas filas tiene nuestro archivo txt...
    // para iterar serialmente atraves de el
    fileName = "jobs/" + fileName;
    numberOfRows = instanceTxt->numberOfRows(fileName);

    for (int i = 0; i < numberOfRows; i++) {
        // instanceTxt->fillTxtStruct(fileName,i);
        lamina_t newLamina = instanceBinary->readBinaryFile
                            (instanceTxt->fillTxtStruct(fileName, i));
        laminas.push_back(newLamina);
    }

    simulacion* simulacionDeCalor = new simulacion;
    #pragma omp parallel num_threads(numberOfThreads) \
        default(none) shared(laminas, simulacionDeCalor, \
                                    instanceWriteBinary)
    {
        #pragma omp for schedule(dynamic)
        for (size_t i = 0; i < laminas.size(); i++) {
            simulacionDeCalor->iniciarSimulacion(laminas[i],
                        laminas[i].rows, laminas[i].columns);
            if (i == 0) {
                instanceWriteBinary->createReportTxt(laminas[i], true);
            } else {
                instanceWriteBinary->createReportTxt(laminas[i], false);
            }
            instanceWriteBinary->createReportBinary(laminas[i]);
        }
    }
    delete simulacionDeCalor;
    delete instanceWriteBinary;
    delete instanceTxt;
    delete instanceBinary;
    return 0;
}

void analyzeArguments(int argc, char* argv[], std::string &fileName,
                                                     int &threads) {
    if (argc < 2) {
        throw std::invalid_argument("Please enter a Job file.");
    }
    if (argc == 2) {
        fileName = argv[1];
        threads = omp_get_max_threads();
    }
    if (argc == 3) {
        fileName = argv[1];
        threads = std::atoi(argv[2]);
    }
}
