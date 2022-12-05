// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#include "simulacion.hpp"

#include <ctime>
#include <iostream>
#include <math.h>
#include <string>
#include <sstream>
#include <vector>

///@brief Recibe el struct de la lamina
// /// y las coordenadas (fila/columna) en que
// ///realiza el cálculo para cambio de temperatura
// /// fórmula dada
// void calculoTemperatura(lamina_t& lamina, size_t fila, size_t columna);
void simulacion::iniciarSimulacion(lamina_t& lamina, size_t filas, size_t columnas){
    lamina_t laminaResultante;
    laminaResultante = lamina;
    bool hayEquilibrio = false;
    time_t start = time(0);
    // printMatrix(lamina, filas, columnas);
    // Mientras no exista equilibrio, se busca el siguiente estado k de la matriz
    while (hayEquilibrio == false) {
        // Se recorre la matriz para calcular el valor de cada celda en el estado k+1
        for (size_t i = 0; i < filas; ++i) {
            for (size_t j = 0; j < columnas; ++j) {
                // Se actualiza el valor de las celdas interiores, en las de los bordes solo
                // se copia el valor de la matriz base
                if ((i != 0) && (j != 0) && (i != (filas-1)) && (j != (columnas-1))) {
                    laminaResultante.matrix[i][j] = calculoTemperatura(lamina, i, j);
                } else {
                    laminaResultante.matrix[i][j] = lamina.matrix[i][j];
                }
            }
        }
        ++lamina.state;
        // Si retorna true, se termina de actualizar los estados 
        hayEquilibrio = verificarEquilibrio(lamina, laminaResultante, filas, columnas);
        copyMatrix(lamina, laminaResultante, filas, columnas);
    }
    // std::cout << "Se hizo en " << lamina.state << " estados";
    time_t finish = time(0);
    lamina.elapsedTime = format_time(finish-start);
        //printMatrix(lamina, filas, columnas);
    }
 

bool simulacion::verificarEquilibrio(lamina_t& laminaBase,lamina_t& laminaResultante, size_t filas, size_t columnas) {
    bool hayEquilibrio = true;
    double epsilon = laminaBase.epsilon;
    for (size_t i = 0; i < filas; ++i) {
        for (size_t j = 0; j < columnas; ++j) {
            if ((i != 0) && (j != 0) && (i != (filas-1)) && (j != (columnas-1))) {
                double cellA = laminaBase.matrix[i][j];
                double cellB = laminaResultante.matrix[i][j];
                if (fabs(cellA-cellB) > epsilon) {
                    hayEquilibrio = false;
                }
            }
        }
    }
    return hayEquilibrio;
}

void simulacion::copyMatrix(lamina_t& laminaBase, lamina_t& laminaResultante, size_t filas, size_t columnas){
    for (size_t i = 0; i < filas; ++i) {
        for (size_t j = 0; j < columnas; ++j) {
            laminaBase.matrix[i][j] = laminaResultante.matrix[i][j];
        }
    }
}

// int abrirArchivo();

// void generarReporte();

// string format_time(const time_t segundos);

// void escribirReporte();

// int abrirReporte();

double simulacion::calculoTemperatura(lamina_t& lamina, size_t fila, size_t columna) {
    
    double estado = 0;
    estado =  lamina.matrix[fila-1][columna];
    estado += lamina.matrix[fila][columna+1];
    estado += lamina.matrix[fila+1][columna];
    estado += lamina.matrix[fila][columna-1];
    estado -= (4* lamina.matrix[fila][columna]);
    //  primero se realiza la multiplicacion
    estado *= ((lamina.time * lamina.diffusion) 
        / (lamina.area*lamina.area));
    estado += lamina.matrix[fila][columna];
    return estado;
}

//

string simulacion::format_time(const time_t seconds) {
    // TODO(any): Using C until C++20 std::format() is implemented by compilers
    char text[48];  // YYYY/MM/DD hh:mm:ss
    const std::tm& gmt = * std::gmtime(&seconds);
    snprintf(text, sizeof text, "%04d/%02d/%02d\t%02d:%02d:%02d", gmt.tm_year
    - 70, gmt.tm_mon, gmt.tm_mday - 1, gmt.tm_hour, gmt.tm_min, gmt.tm_sec);
    return text;
 }

void simulacion::printMatrix(lamina_t& lamina, size_t filas, size_t columnas) {
    for (size_t i = 0; i < filas; ++i) {
        for (size_t j = 0; j < columnas; ++j) {
            std::cout << lamina.matrix[i][j] << "\t";
        }
        std::cout << endl;
    }
    std::cout << endl;
}