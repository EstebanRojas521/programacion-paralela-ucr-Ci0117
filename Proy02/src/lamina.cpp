// // Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// // y Esteban Rojas Carranza - Universidad de Costa Rica.

#include "lamina.hpp"

lamina::lamina(){

}


lamina_t lamina::readBinaryFile(txtData data){
    // Struct que contiene todos los datos listo...
    // para la simulacion de calor
    lamina_t simHitData;

    // Buffer donde leyemos el archivo binario y luego casteamos
    // a enteros/strings segun convenga
    char bufferData[8];
    // Buffer donde leyemos el archivo binario y luego casteamos
    // a los valores de la matriz
    char bufferNumber[8];
    // Iterador para movernos atraves del archivo binario
    //int bufferIterator = 0;
    // Concatenamos nombre de plate name para poder acceder a la carpeta
    data.plateName = "jobs/job001/" + data.plateName;
    //
    //std::cout<<data.plateName<<std::endl;
    // Creamos fstream para leer el archivo binario
    std::fstream file;
    // Abrimos archivo binario
    file.open(data.plateName,std::ios::in|std::ios::binary);

    if(!file.is_open()){
        std::cerr << "Could not read binary file. " << std::endl;
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
        std::cout<<"Rows: "<<simHitData.rows<<" ";
        // Leemos siguientes 8 bytes
        file.read((char *)&bufferData,sizeof(bufferData));
        // Casteamos el buffer a nuestras columns
        simHitData.columns = *(uint64_t*)bufferData;
        std::cout<<"Columns: "<<simHitData.columns<<std::endl;

        
        // std::cout <<"Size: "<< size << std::endl;


        // int current = (int)file.tellp();
        // std::cout <<"Current cursor: "<< current << std::endl;
        // Definimos cuantos bytes nos hacen falta recorrer
        int localRows = 0;
        int localColumns = 1;
        while(file.tellp()<size){
            file.read((char *)&bufferNumber,sizeof(bufferNumber));
            double number = *(double*)bufferNumber;
            std::cout << number << " ";
            if(localColumns == simHitData.columns){
                std::cout<<std::endl;
                localColumns = 0;
            }
            localColumns++;
            // current += 8;
        }

        file.close();
    }
    return simHitData;
}


int lamina::sizeofbinaryFile(std::fstream binaryFile){
    binaryFile.seekp(0,std::ios::end);
    int size = (int)binaryFile.tellp();
    std::cout <<"Size binary file: "<< size << std::endl;
    return size;
}