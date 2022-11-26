// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.
#include "lamina.hpp"
#include <string>
#include <sstream>
#include <fstream>

void lamina(lamina_t& lamina) {
    lamina.columnas = 0;
    lamina.filas = 0;
    lamina.difuTermica = 0;
    lamina.estado = 0;
    lamina.tamanio = 0;
    lamina.tiempo = 0;
    lamina.matriz.clear();
    lamina.matrizNuevoEstado.clear();
}

int read(lamina_t& lamina, string archivoEntrada) {

}

void write(lamina_t& lamina, string archivoSalida) {

}

ifstream &operator>>(ifstream &job, lamina_t &lamina) {

}

ofstream &operator<<(ofstream &reporte, lamina_t &lamina) {

}