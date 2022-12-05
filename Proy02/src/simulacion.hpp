// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#ifndef SIMULACION_HPP
#define SIMULACION_HPP

#include <fstream>
#include <string>
#include "lamina.hpp"

class simulacion {
    double calculoTemperatura(lamina_t& lamina, size_t fila, size_t columna);
    bool verificarEquilibrio(lamina_t& laminaBase, lamina_t& laminaResultante,
                                                 size_t filas, size_t columnas);
    void copyMatrix(lamina_t& laminaBase, lamina_t& laminaResultante,
                                                 size_t filas, size_t columnas);
    std::string format_time(const time_t seconds);

 public:
    simulacion();
    ~simulacion();
    void iniciarSimulacion(lamina_t& lamina, size_t filas, size_t columnas);
};

#endif
