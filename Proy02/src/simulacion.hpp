// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#ifndef SIMULACION_HPP
#define SIMULACION_HPP

#include "lamina.hpp"
#include <string>
#include <fstream>

using namespace std;

class simulacion {
    double calculoTemperatura(lamina_t& lamina, size_t fila, size_t columna);
    bool verificarEquilibrio(lamina_t& laminaBase,lamina_t& laminaResultante,
                 size_t filas, size_t columnas);
    void copyMatrix(lamina_t& laminaBase, lamina_t& laminaResultante, size_t filas, size_t columnas);
    void printMatrix(lamina_t& lamina, size_t filas, size_t columnas);
    string format_time(const time_t seconds);

    public:
    void iniciarSimulacion(lamina_t& lamina, size_t filas, size_t columnas);
};

#endif