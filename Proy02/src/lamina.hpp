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
    ///Tamaño (alto/ancho) - h
    uint64_t tamanio;
    ///Difusivilidad térmica - a
    uint64_t difuTermica;
    /// Matriz
    vector<double>matriz;
};

int read();
void write();

ifstream &operator>>(ifstream &job, lamina_t &lamina);
ofstream &operator<<(ofstream &reporte, lamina_t &lamina);

#endif