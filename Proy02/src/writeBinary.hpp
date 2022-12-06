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
  /**
    *@brief  Constructor of writeBinary
    *@details
    * Constructor used for creating instances
    *@return Nothing. Constructor subrutine.
    */
    writeBinary();

    /**
     * @brief Destructor of writeBinary 
     */
    ~writeBinary();

    /**
    *@brief  Rutines that creates the txt report
    * Rutine where the simHit data is read and the final state
    * state and the finisht time is written into a report
    *@param lamina_t struct that coints the data what will be written
    * the report
    *@param bool it indicates if its the first data, if yes, then 
    * create a new txt file
    *@return Nothing. Void subrutine.
    */
    void createReportTxt(lamina_t& simHitData, bool first);

    /**
    *@brief  Rutines that creates the binary report
    * Rutine where the simHit data is read and the resultant matrix
    * is written into a binary file for further heat sinks if necessary
    *@param lamina_t struct that coints the data what will be written
    * the report
    *@param bool it indicates if its the first data, if yes, then 
    * create a new binary file
    *@return Nothing. Void subrutine.
    */
    void createReportBinary(lamina_t& simHitData, bool first);
};

#endif
