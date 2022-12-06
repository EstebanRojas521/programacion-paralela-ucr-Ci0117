// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#ifndef LAMINA_HPP
#define LAMINA_HPP
#include <stdbool.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "readTxt.hpp"

/**
*@brief  Struct of which contains al data for the heat simulation
*@details
*       A struct which contains all the data for the heat simuluation
*       such as the area,time,epsilon,matrix and difussion
*@param Nothing. Struct type.
*@return Nothing. Struct defnition.
*/
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
    double area;
    /// Difusivilidad térmica - a
    double diffusion;
    /// eplsilon(e)
    double epsilon;
    /// nombre de archivo (lámina)
    std::string plateName;
    /// tiempo de duracion en encontrar equilibrio del plate
    std::string elapsedTime;
    // nombre de archivo (txt)
    std::string fileName;
    /// Matriz original
    std::vector<std::vector<double>> matrix;
};

/**
 * @brief Class lamina that saves info in lamina_t structs 
 */
class lamina{
 public:
    /**
    *@brief  Constructor for lamina class
    *@details
    * Constructor used for creating instances
    *@return Nothing. Constructor subrutine.
    */
    lamina();

    /**
     * @brief Destructor for lamina class
     */
    ~lamina();

    /**
    *@brief  Reads the binary file
    *@details
    *   Reads the binary file and stores it at the
    *   lamina_t for the eventual heat simulation
    *@param data struct wich contain the palete name
    *@return the lamina_t struct ready for the heat simulation
    */
    lamina_t readBinaryFile(txtData data);

 private:
    /**
    *@brief  Transfers the data from the txtData struct to the lamina_t struct
    *@details
    *   Transfers the data from the txtData to the lamina_t with things 
    *   such as the file name and the palete name for further use    
    *@param txtData struct wich will give data
    *@param binaryData struct which will recieve data
    *@return Nothing. Void subrutine.
    */
    void equalValues(txtData &txtData, lamina_t &binaryData);
};

#endif
