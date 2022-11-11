// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#include "AppAssembler.hpp"


AppAssembler::AppAssembler(HttpPackage& package)
    :package(package){
        
    }


int AppAssembler::run(){
    this->consumeForeverASBM();

    return 0;
}


void AppAssembler::consumeASBM(GoldbachStruct data){
    data = data;

    // //std::cout<<"Im in AppAssembler"<<std::endl;
    // std::cout<<"Number: "<<data.number<<std::endl;
    // if(data.number%2 == 0){
    //     std::cout<<"Sums: "<<data.resultsVector.size()/2<<std::endl;
    // }
    // for(int i = 0;i<data.resultsVector.size();i++){
    //    // std::cout<<": "<<data.number<<std::endl;
    // }
    // //aca imprimo resultados
}