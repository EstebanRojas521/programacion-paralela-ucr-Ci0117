// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#ifndef LAMINA_HPP
#define LAMINA_HPP
#include <stdbool.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "readTxt.hpp"

struct lamina_t {
    /// Cantidad de filas - R
    uint64_t rows;
    /// Cantidad de columnas - C
    uint64_t columns;
    /// Estado - k
    double state;
    /// Tiempo - t
    uint64_t time;
    /// Tamaño (alto/ancho) - h
    double area;
    /// Difusivilidad térmica - a
    double diffusion;
    /// eplsilon(e)
    double epsilon;
    /// nombre de archivo (lámina)
    std::string plateName;
    /// tiempo de duracion en encontrar equilibrio del plate
    std::string elapsedTime;
    // nombre de archivo (txt)
    std::string fileName;
    /// Matriz original
    std::vector<std::vector<double>>matrix;
};

class lamina{
    public:
    lamina();
    lamina_t readBinaryFile(txtData data);
    void printOriginalMatrix(lamina_t &binaryData);
    private:
    void equalValues(txtData &txtData,lamina_t &binaryData);
};

#endif