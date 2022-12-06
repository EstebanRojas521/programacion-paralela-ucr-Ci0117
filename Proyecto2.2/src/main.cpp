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

void analyzeArguments(int argc, char* argv[],
 std::string &fileName, int &threads);
int calculate_start(int rank, int end, int workers, int begin);
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

        for (size_t i = 0; i < numberOfRows; i++) {
            // instanceTxt->fillTxtStruct(fileName,i);
            lamina_t newLamina = instanceBinary->readBinaryFile
                                (instanceTxt->fillTxtStruct(fileName, i));
            laminas.push_back(newLamina);
        }
        const int overall_start = 0;
        const int overall_finish = laminas.size();
        const int process_start = calculate_start(process_number, overall_finish
        , process_count, overall_start);
        const int process_finish = calculate_finish(process_number,
        overall_finish, process_count, overall_start);
         std::cout << process_hostname << ':' << process_number << ": range ["
        << process_start << ", " << process_finish << " ]" << std::endl;
        simulacion* simulacionDeCalor = new simulacion;
        #pragma omp parallel num_threads(numberOfThreads) \
        default(none) shared(laminas, simulacionDeCalor, \
        instanceWriteBinary, process_start, process_finish, std::cout, \
        process_hostname, process_number ) {
            int thread_start = -1;
            int thread_finish = -1;
            #pragma omp for
            for (int index = process_start; index < process_finish; ++index) {
                if (thread_start == -1) {
                    thread_start = index;
                }
                thread_finish = index;
            }
            ++thread_finish;
            if (thread_start != -1) {
                #pragma omp for
                for (int i = thread_start; i <thread_finish ; i++) {
                    simulacionDeCalor->iniciarSimulacion(laminas[i],
                                laminas[i].rows, laminas[i].columns);
                    if (i == 0) {
                        instanceWriteBinary->createReportTxt(laminas[i], true);
                    } else {
                        instanceWriteBinary->createReportTxt(laminas[i], false);
                    }
                    instanceWriteBinary->createReportBinary(laminas[i]);
                }
                #pragma omp critical(can_print)
                std::cout << '\t' << process_hostname << ':' <<
                process_number << '.'<< omp_get_thread_num() <<
                ": range [" << thread_start << ", " <<thread_finish
                << "[ " << std::endl;
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
