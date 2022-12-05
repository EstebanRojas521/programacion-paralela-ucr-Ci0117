// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.
#ifndef READTXT_HPP
#define READTXT_HPP

#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <stdbool.h>
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
    /**
    *@brief  Constructor for readText
    *@details
    * Constructor used for creating instances
    *@return Nothing. Constructor subrutine.
    */
    readText();
    /**
    *@brief  Retuns number of rows in a .txt file
    *@details
    *   Reads the binary file and stores it at the
    *   lamina_t for the eventual heat simulation
    *@param string name of the file we wanna know the number of rows
    *@return the number of rows of the file
    */
    int numberOfRows(std::string fileName);
    /**
    *@brief  Fills the txt struct
    *@details
    *   Reads the txt file and stores it at the
    *   txt for the eventual heat simulation
    *@param string name of the file we wanna know the number of rows
    *@param int especific line of the filename we will read
    *@return the txtData struct ready for further use
    */
    txtData fillTxtStruct(std::string fileName,int lineNumber);
    private:
    /**
    *@brief  Takes the data of a especific line and saves it in a struct
    *@details
    *   Reads a especific line and saves it in a txt struct
    *@param string data of the line that was read
    *@return the txtData struct ready for further use
    */
    txtData createStruct(std::string data);
      /**
    *@brief  Prints the txtData struct
    *@details
    *   Prints the txData struct for it to be checked
    *   if necessary. Prints in console.
    *@param txtData data that will be printed
    *@return Nothing. Void subrutine.
    */
    void printTxtStruct(txtData data);
};

#endif
