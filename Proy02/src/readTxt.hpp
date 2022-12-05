// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.
#ifndef READTXT_HPP
#define READTXT_HPP

#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <stdbool.h>
#include <string>


// Struct que contiene los datos del archivo txt...
// para luego convertirlos a binario
struct txtData{
    std::string plateName;
    std::string fileName;
    uint64_t time;
    double diffusion;
    double area;
    double epsilon;
    bool dataIsComplete = false;
};

class readText{
    public:
    readText();
    int numberOfRows(std::string fileName);
    txtData fillTxtStruct(std::string fileName,int lineNumber);
    private:
    txtData createStruct(std::string data);
    void printTxtStruct(txtData data);
};

#endif
