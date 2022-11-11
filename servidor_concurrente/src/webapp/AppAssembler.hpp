// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#ifndef APPASSEMBLER_HPP
#define APPASSEMBLER_HPP

#include <vector>
#include "Consumer.hpp"
#include "Assembler.hpp"
#include "Socket.hpp"
#include "TcpServer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "HttpConnectionHandler.hpp"
#include "Queue.hpp"
#include "HttpServer.hpp"
#include "HttpApp.hpp"
#include "HttpPackage.hpp"
#include "GoldbachStruct.hpp"

class AppAssembler: public Assembler<GoldbachStruct>{

    //talvez haya que poner referencia
    HttpPackage package;

    public:
    
    explicit AppAssembler(HttpPackage& httpPackage);
    int run() override; 
    void consumeASBM(GoldbachStruct data) override;
};

#endif