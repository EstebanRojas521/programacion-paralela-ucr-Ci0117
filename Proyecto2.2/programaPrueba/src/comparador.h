#ifndef COMPARADOR
#define COMPARADOR

#include "../../src/lamina.hpp"

class comparador{

    public:
     /**
    * @brief Reads the binary file and saves it into a struct
    * @param txtData struct which contains the binary file that will be read
    */
    lamina_t readBinaryFile(txtData data);
       /**
    * @brief Compares the matrix we wished to obtain, and the matrix we obtained
    * @param lamina_t struct which contains the matrix that will be compared
    * @param lamina_t struct which contains the matrix that will be compared
    */
    bool compare(lamina_t laminaA, lamina_t laminaB);
};

#endif