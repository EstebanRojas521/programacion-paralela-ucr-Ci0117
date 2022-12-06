// // Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// // y Esteban Rojas Carranza - Universidad de Costa Rica.

#include "lamina.hpp"

lamina::lamina() {}

lamina::~lamina() {}

/**
*@brief  Initialize the lamina_t struct
*@details
*   Intialize al the lamina_t stuct variables
*@param lamina_t reference to the struct that will be initalized
*@return Nothig. Void subrutine.
*/
void initValues(lamina_t& lamina) {
    lamina.area = 0;
    lamina.columns = 0;
    lamina.diffusion = 0;
    lamina.elapsedTime = "";
    lamina.epsilon = 0;
    lamina.plateName = "";
    lamina.rows = 0;
    lamina.state = 0;
    lamina.time = 0;
}


lamina_t lamina::readBinaryFile(txtData data) {
    
    // Struct que contiene todos los datos listo...
    // para la simulacion de calor
    lamina_t simHitData;
    // Inicialiamos los valores del struct
    initValues(simHitData);
    //Igualamops los valores del archivo de texto con el binario
    this->equalValues(data,simHitData);
    // Buffer donde leyemos el archivo binario y luego casteamos
    // a enteros/strings segun convenga
    char bufferData[8];
    // Buffer donde leyemos el archivo binario y luego casteamos
    // a los valores de la matriz
    char bufferNumber[8];
    // Concatenamos nombre de plate name para poder acceder a la carpeta
    data.plateName = "jobs/" + data.plateName;
    // Creamos fstream para leer el archivo binario
    std::fstream file;
    // Abrimos archivo binario
    file.open(data.plateName,std::ios::in|std::ios::binary);
    //file.open("output/plate001-2.bin",std::ios::in|std::ios::binary);
    if (!file.is_open()){
        std::cerr << "Could not read binary file in lamina. " << std::endl;
        return simHitData;
    } else {
        file.seekp(0, std::ios::end);
        int size = static_cast<int>(file.tellp());
        // Ponemos cursos de lectura al principio del archivo
        file.seekp(0, std::ios::beg);
        // Leemos primeros 8 bytes del archivo binario
        file.read(reinterpret_cast<char *>(&bufferData), sizeof(bufferData));
        // Casteamos el buffer a nuestras filas
        simHitData.rows = *reinterpret_cast<uint64_t*>(bufferData);
        // Leemos siguientes 8 bytes
        file.read(reinterpret_cast<char *>(&bufferData), sizeof(bufferData));
        // Casteamos el buffer a nuestras columns
        simHitData.columns = *reinterpret_cast<uint64_t*>(bufferData);
        // std::cout<<"Columns: "<<simHitData.columns<<std::endl;
        // Iterador local de columnas
        uint64_t localColumns = 1;
        // Vector temporal
        std::vector<double> localVector;
        // Recorremos los bytes restante del archivo -> los numeros...
        // de la matriz
        while (file.tellp() < size) {
            file.read(reinterpret_cast<char *>(&bufferNumber),
                                         sizeof(bufferNumber));
            double number = *reinterpret_cast<double*>(bufferNumber);
            localVector.push_back(number);
            if (localColumns == simHitData.columns) {
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
    // Regresamos nuestros datos listos para la transferencia de calor
    return simHitData;
}


void lamina::equalValues(txtData &txtData, lamina_t &binaryData) {
    // Igualamos los valores obtenidos en el archivo de texto
    // con el archivo binario
    binaryData.fileName = txtData.fileName;
    binaryData.plateName = txtData.plateName;
    binaryData.time = txtData.time;
    binaryData.diffusion = txtData.diffusion;
    binaryData.area = txtData.area;
    binaryData.epsilon = txtData.epsilon;
    binaryData.state = 0;
}
