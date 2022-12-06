#ifndef COMPARADOR
#define COMPARADOR

#include "../../src/lamina.hpp"

class comparador{

    public:
    lamina_t readBinaryFile(txtData data);
    bool compare(lamina_t laminaA, lamina_t laminaB);
};

#endif