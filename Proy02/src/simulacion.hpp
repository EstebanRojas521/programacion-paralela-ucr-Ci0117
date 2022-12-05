// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#ifndef SIMULACION_HPP
#define SIMULACION_HPP

#include <fstream>
#include <string>
#include "lamina.hpp"

class simulacion {

 private:
    /**
    *@brief  Rutine where the heat sim  for a especif square is obtained
    *  Rutine where the data from lamina_t is read and
    *  the heat for a especific square is obtained
    *@param lamina_t struct wich contains the data for the hit sim
    *@param size_t number of rows of the hit sim matrix
    *@param size_t number of columns of the hit sim matrix
    *@return the temperature for the actual square
    */
    double calculoTemperatura(lamina_t& lamina, size_t fila, size_t columna);

    /**
    *@brief  Rutine that checks if the heat balance has been reached
    *   Rutine that checks if the heat balance has been reached, if
    * yes, the return true. If not, return false.
    *@param lamina_t struct wich contains the data of the actual iteration
    *@param lamina_t struct wich contains the data of the next iteration
    *@param size_t number of rows of the hit sim matrix
    *@param size_t number of columns of the hit sim matrix
    *@return If the heat balance has been reach or not
    */
    bool verificarEquilibrio(lamina_t& laminaBase, lamina_t& laminaResultante,
                                                 size_t filas, size_t columnas);

    /**
    *@brief  Rutine that copies one matrix into another one
    *@param lamina_t struct wich contains the data of the actual iteration
    *@param lamina_t struct wich contains the data of the next iteration
    *@param size_t number of rows of the hit sim matrix
    *@param size_t number of columns of the hit sim matrix
    *@return Nothing. Void subrutine.
    */
    void copyMatrix(lamina_t& laminaBase, lamina_t& laminaResultante,
                                                 size_t filas, size_t columnas);

    /**
    *@brief  Rutine that prints a matrix
    *@param lamina_t struct wich contains the data that will be printed
    *@param size_t number of rows of the hit sim matrix
    *@param size_t number of columns of the hit sim matrix
    *@return Nothing. Void subrutine.
    */
    void printMatrix(lamina_t& lamina, size_t filas, size_t columnas);

    /**
    *@brief  Rutine that tells the time where the heat sim finished
    *@param time_t number of seconds where the heat sim finished
    *@return the time where the heat sim finished
    */
    string format_time(const time_t seconds);

 public:
    /**
     * @brief Constructor of simulacion class
     */
    simulacion();

    /**
     * @brief Destructor of simulacion class
     */
    ~simulacion();

    /**
    *@brief  Rutine where the heat sim is executed
    *@details
    *  Rutine where the data from lamina_t is read and
    *  the resultant matrix is obtained. It acts as a "main"
    *  for this class. Multiple subrutines are called.
    *@param lamina_t struct wich contains the data for the hit sim
    *@param size_t number of rows of the hit sim matrix
    *@param size_t number of columns of the hit sim matrix
    *@return Nothing. Void subrutine.
    */
    void iniciarSimulacion(lamina_t& lamina, size_t filas, size_t columnas);
};

#endif
