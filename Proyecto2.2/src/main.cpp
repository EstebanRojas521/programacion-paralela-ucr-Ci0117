// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.
#include <mpi.h>
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
void analyzeArguments(int argc, char* argv[],
 std::string &fileName, int &threads);

 /**
 * @brief Method that tells the mpi process when to start
 * @param rank number used for formula
 * @param end number used for formula
 * @param workers workers used for formula
 * @param begin number used for formula
 */
int calculate_start(int rank, int end, int workers, int begin);

 /**
 * @brief Method that tells the mpi process when to finish
 * @param rank number used for formula
 * @param end number used for formula
 * @param workers workers used for formula
 * @param begin number used for formula
 */
int calculate_finish(int rank, int end, int workers, int begin);

int main(int argc, char* argv[]) {
    if (MPI_Init(&argc, &argv) == MPI_SUCCESS) {
        readText* instanceTxt = new readText();
        lamina* instanceBinary = new lamina();
        writeBinary* instanceWriteBinary = new writeBinary();
        int process_number = -1;  // rank
        MPI_Comm_rank(MPI_COMM_WORLD, &process_number);
        int process_count = -1;
        MPI_Comm_size(MPI_COMM_WORLD, &process_count);
        char process_hostname[MPI_MAX_PROCESSOR_NAME];
        int hostname_length = -1;
        MPI_Get_processor_name(process_hostname, &hostname_length);
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
        const int overall_start = 0;
        const int overall_finish = numberOfRows;
        const int process_start = calculate_start(process_number, overall_finish
        , process_count, overall_start);
        const int process_finish = calculate_finish(process_number,
        overall_finish, process_count, overall_start);
        for (int i = process_start; i < process_finish; i++) {
            lamina_t newLamina = instanceBinary->readBinaryFile
            (instanceTxt->fillTxtStruct(fileName, i));
            laminas.push_back(newLamina);
        }
        simulacion* simulacionDeCalor = new simulacion;
        #pragma omp parallel num_threads(numberOfThreads) \
        default(none) shared(laminas, simulacionDeCalor, \
                            instanceWriteBinary, std::cout, process_number)
        {
        #pragma omp for schedule(dynamic)
        for (size_t i = 0; i < laminas.size(); i++) {
            simulacionDeCalor->iniciarSimulacion(laminas[i],
                        laminas[i].rows, laminas[i].columns);
            if (process_number == 0 && omp_get_thread_num() == 0) {
                instanceWriteBinary->createReportTxt(laminas[i], false);
            } else {
                instanceWriteBinary->createReportTxt(laminas[i], false);
            }
            // #pragma omp critical(can_write_report)
            instanceWriteBinary->createReportBinary(laminas[i]);
        }
        }
        delete simulacionDeCalor;
        delete instanceWriteBinary;
        delete instanceTxt;
        delete instanceBinary;
        MPI_Finalize();
    } else {
        std::cerr << "Could not start MPI" << std::endl;
    }
    return 0;
}

void analyzeArguments(int argc, char* argv[], std::string
&fileName, int &threads) {
    if (argc < 2) {
        throw std::invalid_argument("Please enter a Job file.");
    }
    if (argc == 2) {
        fileName = argv[1];
        threads = 10;
    }
    if (argc == 3) {
        fileName = argv[1];
        threads = std::atoi(argv[2]);
    }
}

int calculate_start(int rank, int end, int workers, int begin) {
    const int range = end - begin;
    return begin + rank * (range/workers) + std::min(rank, range%workers);
}

int calculate_finish(int rank, int end, int workers, int begin) {
  return calculate_start(rank + 1, end, workers, begin);
}
