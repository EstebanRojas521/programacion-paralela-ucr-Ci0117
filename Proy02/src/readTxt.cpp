// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#include "readTxt.hpp"



// constructor vacio
readText::readText(){

}

txtData readText::fillTxtStruct(std::string fileName,int lineNumber){
    // struct que contiene los datos de la linea
    txtData data;
    // If stream del archivo
    std::ifstream myFile;
    // Iterardor que nos dice en que linea estamos
    int currentLine = 0;
    // Linea especifica que vamos a leer
    std::string lineData;;
    // Abrimos  archivo de texto
    myFile.open(fileName);
    // Tiramos error si no logramos abrir el archivo de texto
    if(myFile.fail()){
        std::cerr<< "Could not read txt file"<<std::endl;
        return data;
    }
    // Iteramos atraves del archivo para leer nuestra linea especifica
    while((!myFile.eof())&&lineNumber!=-1){
        std::getline(myFile,lineData);
        // Condicion de parada -> encontramos nuestra linea
        if(currentLine == lineNumber){
            lineNumber = -1;
        }
        currentLine++;
    }

    // Tenemos la linea que queremos, pero ahora tenemos que 
    // separar sus datos(difusio,tiempo,area etc...)
    //std::cout << lineData <<std::endl;
    data = this->createStruct(lineData);
    // Cerramos archivo de texto
    myFile.close();

    printTxtStruct(data);
    return data;
}

txtData readText::createStruct(std::string lineData){
    // Struct que vamos a llenar 
    txtData txtData;
    // Espacio de la linea que queremos agregar
    // al struct
    int spotNumber = 0;
    // Stringsstream para iterar por el arreglo
    std::stringstream ss(lineData);
    // Variable que vamos a agregar
    std::string word;
    while (ss >> word) {
        if(spotNumber == 0)
            txtData.plateName = word;
        if(spotNumber == 1)
            txtData.time = std::stoull(word);
        if(spotNumber == 2)
            txtData.diffusion =std::stod (word);
        if(spotNumber == 3)
            txtData.area = std::stod (word);
        if(spotNumber == 4){
            // Tenemos todos los datos  se puede 
            // comenzar el proceso de calor
            txtData.dataIsComplete = true;
            txtData.epsilon = std::stod (word);
        }
        spotNumber++;
    }
    return txtData;
}



int readText::numberOfRows(std::string fileName){
    // Variable que nos va a indicar cuantas filas
    // tiene el txt
    int rows = 0;
    // Fstream del archivo
    std::fstream myFile;
    // Abrimos archivo
    myFile.open(fileName);
    // Iteramos atraves del archivo
    if(myFile.is_open()){
        std::string line;
        while(std::getline(myFile,line)){
            // Si hay una fila, sumamos
            rows++;
        };
        // Cerramos archivp
        myFile.close();
    }

    // Regresamos el numero de filas
    return rows;
}

void readText::printTxtStruct(txtData data){
    std::cout<< data.plateName <<" ";
    std::cout<< data.time <<" ";
    std::cout<< data.diffusion <<" ";
    std::cout<< data.area <<" ";
    std::cout<< data.epsilon <<std::endl;
}