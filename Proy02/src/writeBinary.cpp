// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#include "writeBinary.hpp"

writeBinary::writeBinary(){

}


void writeBinary::createReportTxt(lamina_t simHitData,bool first){
    // Creamos ofstream del archivo donde vamos a escribir
    std::ofstream file; 
    // Eliminamos el directorio "jobs/" de nuestro filename
    simHitData.fileName.erase(0,5);
    // Eliminamos el directorio ".txt" de nuestro archivo
    simHitData.fileName.erase(6,4);
    // Creamos nuestro nuevo filename(job###.tsv) para el reporte
    simHitData.fileName = "output/"+simHitData.fileName + ".tsv";
    // Si el archivo existe, lo borrramos para sobrescribirlo...
    // con los datos de nuestra nueva simulacion
    if(first == true){
        char fileBuffer[20];
        strcpy(fileBuffer, simHitData.fileName.c_str());
        remove(fileBuffer);
    }
    // Abrimos el archivo 
    file.open(simHitData.fileName,std::ios::in | std::ios::app);
    if(file.is_open()){
        file << simHitData.plateName << " ";
        file << simHitData.time << " ";
        file << simHitData.diffusion << " ";
        file << simHitData.area << " ";
        file << simHitData.epsilon << " ";
        file << simHitData.state << " ";
        file << "Not implemented yet" << " " << std::endl;
        file.close();
    } else{
        std::cerr << "Could not write results on .tsv file " << std::endl;
    }
}   

void writeBinary::createReportBinary(lamina_t simHitData,bool first){
    
    // Buffer donde almacenamos filas, columnas y numeros
    // para nuestro archivo binario
    char buffer[8];
    // Eliminamos el ".bin" para crear correctamente nuestra...
    // direccion
    simHitData.plateName.erase(8,6);
    // Obtenemos el estado final para nuestra direccion
    int state = (int)simHitData.state;
    // Creamos la direccion de nuestro archivo de salida
    simHitData.plateName = "output/"+simHitData.plateName +"-"+std::to_string(state)+".bin";
    //std::cout << simHitData.plateName << std::endl;
    // Si el archivo existe, lo borrramos para sobrescribirlo...
    // con los datos de nuestra nueva simulacion
    if(first == true){
        char fileBuffer[20];
        strcpy(fileBuffer, simHitData.plateName.c_str());
        remove(fileBuffer);
    }
    // Creamos fstream del archivo binario
    std::fstream file;
    // Abrimos archivo binario
    file.open(simHitData.plateName,std::ios::binary|std::ios::out);
    if(!file.is_open()){
        std::cerr << "Could not read binary file in binary report. " << std::endl;
    } else {
        // Escribimos nuestras filas en el archivo binario de salida
        file.write(reinterpret_cast<char*>(&simHitData.rows),8);
        // Escribimos nuestras columns en el archivo binario de salida
         file.write(reinterpret_cast<char*>(&simHitData.columns),8);
        // Escribimos nuestra matriz
        int rows = simHitData.rows;
        int columns = simHitData.columns;
        for(int i = 0;i <rows;i++){
            for(int j = 0;j <columns;j++){
                double number = simHitData.matrix[i][j];
                file.write(reinterpret_cast<char*>(&number),8);
            }  
        }
        // Cerramos el archivo binario de salida
        file.close();   
    }
}
