// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#ifndef LAMINA_HPP
#define LAMINA_HPP
#include <stdbool.h>
#include <fstream>
#include <iostream>
//#include <sctring>
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
    uint64_t size;
    /// Difusivilidad térmica - a
    uint64_t diffusion;
    /// nombre de archivo (lámina)
    std::string fileName;
    /// Matriz original
    std::vector<std::vector<double>>matrix;
    /// @brief  Matriz con cambio de estado
    std::vector<std::vector<double>>resultantMatrix;
};

class lamina{
    public:
    lamina();
    lamina_t readBinaryFile(txtData data);
    int sizeofbinaryFile(std::fstream binaryFile);
};

#endif