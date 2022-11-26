// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#include "simulacion.hpp"

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

struct simulacion_t {
    //cantidad de hilos, nombres de archivos
    //lamina que lee
};


int iniciarSimulacion();
/// @brief Recibe el struct de la lamina
/// y las coordenadas (fila/columna) en que
///realiza el cálculo para cambio de temperatura
/// fórmula dada
void calculoTemperatura(lamina_t &lamina, size_t fila, size_t columna);

int abrirArchivo();

void generarReporte();

string format_time(const time_t segundos);


void calculoTemperatura(lamina_t &lamina, size_t fila, size_t columna) {
   /* crear la matriz
    size_t estado = 0.0;
    estado =  lamina.estado[fila-1][columna];
    estado += lamina.estado[fila][columna+1];
    estado += lamina.estado[fila+1][columna];
    estado += lamina.estado[fila][columna-1];
    estado -= 4* lamina.estado[fila][columna];
    //  primero se realiza la multiplicacion
    estado *= (lamina.tiempo * lamina.difuTermica 
        / (lamina.tamanio*lamina.tamanio));
    estado += lamina.estado[fila][columna];
    */
}