// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#include "simulacion.hpp"

#include <ctime>
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
void calculoTemperatura(lamina_t& lamina, size_t fila, size_t columna);

int abrirArchivo();

void generarReporte();

string format_time(const time_t segundos);

void escribirReporte();

int abrirReporte();

void calculoTemperatura(lamina_t& lamina, size_t fila, size_t columna) {

    double estado;
    estado =  lamina.matriz[fila-1][columna];
    estado += lamina.matriz[fila][columna+1];
    estado += lamina.matriz[fila+1][columna];
    estado += lamina.matriz[fila][columna-1];
    estado -= 4* lamina.matriz[fila][columna];
    //  primero se realiza la multiplicacion
    estado *= (lamina.tiempo * lamina.difuTermica 
        / (lamina.tamanio*lamina.tamanio));
    estado += lamina.matriz[fila][columna];

}

string format_time(const time_t seconds) {
  // TODO(any): Using C until C++20 std::format() is implemented by compilers
  char text[48];  // YYYY/MM/DD hh:mm:ss
  const std::tm& gmt = * std::gmtime(&seconds);
  snprintf(text, sizeof text, "%04d/%02d/%02d\t%02d:%02d:%02d", gmt.tm_year
    - 70, gmt.tm_mon, gmt.tm_mday - 1, gmt.tm_hour, gmt.tm_min, gmt.tm_sec);
  return text;
}
