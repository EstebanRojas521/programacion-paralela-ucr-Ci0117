// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#ifndef WRITEBINARY_HPP
#define WRITEBINARY_HPP
#include <stdbool.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "lamina.hpp"


class writeBinary{
 public:
    writeBinary();
    ~writeBinary();
    void createReportTxt(lamina_t simHitData, bool first);
    void createReportBinary(lamina_t simHitData, bool first);
};

#endif
