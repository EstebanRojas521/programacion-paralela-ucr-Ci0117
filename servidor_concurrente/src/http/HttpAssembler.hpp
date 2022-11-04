// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#ifndef HTTPASSEMBLER_HPP
#define HTTPASSEMBLER_HPP

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

Class HttpAssembler: public Assembler<HttpPackage>{
    DISABLE_COPY(AssemblerTest);

    protected:

    public:

    explicit HttpAssembler();

    int run() override;

    void consumeASBM(NetworkMessage data) override;

};

#endif