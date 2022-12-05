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
    simHitData.fileName = simHitData.fileName + ".tsv";
    // Si el archivo existe, lo borrramos para sobrescribirlo...
    // con nuestra nueva simulacion
    if(first == true){
        char fileBuffer[20];
        strcpy(fileBuffer, simHitData.fileName.c_str());
        remove(fileBuffer);
    }
    // Abrimos el archivo 
    file.open(simHitData.fileName,std::ios::in | std::ios::app);
    if(file.is_open()){
        file << simHitData.area << std::endl;
        file.close();
    }
}   

void writeBinary::createReportBinary(lamina_t simHitData){
    simHitData = simHitData;
}