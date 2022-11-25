// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.
#include <string>
#include "Dispatcher.hpp"
#include "HttpPackage.hpp"
#ifndef HTTPDISPATCHER_HPP
#define HTTPDISPATCHER_HPP

// ocupa un key y lo que vaya a producir
class HttpDispatcher : public Dispatcher <std::string, HttpPackage>{
    DISABLE_COPY(HttpDispatcher);

 protected:
    // variables globales que quiero aqui -> aun no se


 public:
    // constructor -> por el momento vacio
    HttpDispatcher();
    int run() override;

    // void consume(HttpPackage package) override;
    bool serveNotFound(HttpPackage& httpPackage);
    // el key si no me equivoco es de tipo string
    std::string extractKey(HttpPackage& package)  override;
};

#endif
