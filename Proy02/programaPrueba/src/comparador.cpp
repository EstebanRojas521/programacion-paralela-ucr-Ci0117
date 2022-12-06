#include "comparador.h"
#include <iostream>
#include <math.h>

lamina_t comparador::readBinaryFile(txtData data){
    // Struct que contiene todos los datos listo...
    // para la simulacion de calor
    lamina_t simHitData;

    // Buffer donde leyemos el archivo binario y luego casteamos
    // a enteros/strings segun convenga
    char bufferData[8];
    // Buffer donde leyemos el archivo binario y luego casteamos
    // a los valores de la matriz
    char bufferNumber[8];
    // Creamos fstream para leer el archivo binario
    std::fstream file;
    // Abrimos archivo binario
    file.open(data.plateName,std::ios::in|std::ios::binary);
    if(!file.is_open()){
        std::cerr << "Could not read binary file. " << std::endl;
        std::cout << data.plateName << std::endl;
        return simHitData;
    } else {
        file.seekp(0,std::ios::end);
        int size = (int)file.tellp();
        //std::cout <<"Size: "<< size << std::endl;
        // Ponemos cursos de lectura al principio del archivo
        file.seekp(0,std::ios::beg);
        // Leemos primeros 8 bytes del archivo binario
        file.read((char *)&bufferData,sizeof(bufferData));
        // Casteamos el buffer a nuestras filas
        simHitData.rows = *(uint64_t*)bufferData;
        // Leemos siguientes 8 bytes
        file.read((char *)&bufferData,sizeof(bufferData));
        // Casteamos el buffer a nuestras columns
        simHitData.columns = *(uint64_t*)bufferData;
        // Iterador local de columnas
        uint64_t localColumns = 1;
        // Vector temporal
        std::vector<double>localVector;
        // Recorremos los bytes restante del archivo -> los numeros...
        // de la matriz
        while(file.tellp()<size){
            file.read((char *)&bufferNumber,sizeof(bufferNumber));
            double number = *(double*)bufferNumber;
            localVector.push_back(number);
            if(localColumns == simHitData.columns){
                // Igualamos nuestro vector local a nuestra matrix
                simHitData.matrix.push_back(localVector);
                // Limpiamos el vector para la siguiente fila
                localVector.clear();  
                // Ya imprimimos todos las columnas de esta fila...
                // entonces reiniciamos contador de columnas
                localColumns = 0;
            }
            localColumns++;
        }
        // Cerramos lectura de archivo binario
        file.close();
    }
    
    //this->printOriginalMatrix(simHitData);
    //Regresamos nuestros datos listos para la transferencia de calor
    return simHitData;
}

bool comparador::compare(lamina_t laminaA, lamina_t laminaB) {
    bool iguales = true;
    if (laminaA.rows == laminaB.rows && laminaA.columns == laminaB.columns) {
        size_t filas = laminaA.rows;
        size_t columnas = laminaA.columns;
        double epsilon = laminaA.epsilon;
        for (size_t i = 0; i < filas; ++i) {
            for (size_t j = 0; j < columnas; ++j) {
                double cellA = laminaA.matrix[i][j];
                double cellB = laminaB.matrix[i][j];
                if (fabs(cellA-cellB) > epsilon) {
                    iguales = false;
                }
            }
        }
    } else {
        iguales = false;
    }
    return iguales;
}