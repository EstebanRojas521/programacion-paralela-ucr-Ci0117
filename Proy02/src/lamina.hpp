// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#ifndef LAMINA_HPP
#define LAMINA_HPP

#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct lamina_t {
    /// Cantidad de filas - R
    uint64_t filas;
    /// Cantidad de columnas - C
    uint64_t columnas;
    /// Estado - k
    uint64_t estado;
    /// Tiempo - t
    uint64_t tiempo;
    /// Tamaño (alto/ancho) - h
    uint64_t tamanio;
    /// Difusivilidad térmica - a
    uint64_t difuTermica;
    /// nombre de archivo (lámina)
    string nombreArchivo;
    /// Matriz original
    vector<vector<double>>matriz;
    /// @brief  Matriz con cambio de estado
    vector<vector<double>>matrizNuevoEstado;
};

class lamina{

};

#endif