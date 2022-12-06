// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.
#ifndef READTXT_HPP
#define READTXT_HPP

#include <stdbool.h>
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>

/**
*@brief  Struct of which contains al data of the txt
*@details
*   Stuct which contains the from the txt, such as
*   the time,difussion,area,epsilon
*@param Nothing. Struct type.
*@return Nothing. Struct defnition.
*/
struct txtData{
    // Name of plate
    std::string plateName;
    // Name of file
    std::string fileName;
    // Time of each state
    uint64_t time;
    // Thermal diffusion
    double diffusion;
    // Area of a square
    double area;
    // Balance point
    double epsilon;
};

/**
 * @brief Class that analizes job.txt files
 */
class readText{
 public:
    /**
    *@brief  Constructor for readText
    *@details
    * Constructor used for creating instances
    *@return Nothing. Constructor subrutine.
    */
    readText();

    /**
     * @brief Destructor for readText class
     */
    ~readText();

    /**
    *@brief  Retuns number of rows in a .txt file
    *@details
    *   Reads the binary file and stores it at the
    *   lamina_t for the eventual heat simulation
    *@param fileName name of the file we wanna know the number of rows
    *@return the number of rows of the file
    */
    int numberOfRows(std::string fileName);

    /**
    *@brief  Fills the txt struct
    *@details
    *   Reads the txt file and stores it at the
    *   txt for the eventual heat simulation
    *@param fileName name of the file we wanna know the number of rows
    *@param lineNumber especific line of the filename we will read
    *@return the txtData struct ready for further use
    */
    txtData fillTxtStruct(std::string fileName, int lineNumber);

 private:
    /**
    *@brief  Takes the data of a especific line and saves it in a struct
    *@details
    *   Reads a especific line and saves it in a txt struct
    *@param data data of the line that was read
    *@return the txtData struct ready for further use
    */
    txtData createStruct(std::string data);

    /**
    *@brief  Prints the txtData struct
    *@details
    *   Prints the txData struct for it to be checked
    *   if necessary. Prints in console.
    *@param data data that will be printed
    *@return Nothing. Void subrutine.
    */
    void printTxtStruct(txtData data);
};

#endif
