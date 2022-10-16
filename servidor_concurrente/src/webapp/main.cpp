// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0
// Serial web server's initial code for parallelization

#ifdef WEBSERVER

#include "HttpServer.hpp"
#include "FactWebApp.hpp"
#include "GoldbachWebApp.hpp"

//crea servidor web = abstracto = codigo reutilizable = agnostico de lo que le voy a pedir

//aplicacion web = depende del contexto 

//servidores tienen start, restart, stop , config, test, test_config 

//HTTP -> depende de NETWORK

/// Start the web server
int main(int argc, char* argv[]) {
  // Create the web server
  //HttpServer httpServer;
  // Create a factorization web application, and other apps if you want
  //FactWebApp factWebApp;
  GoldbachWebApp goldbachWebApp;
  // Register the web application(s) with the web server
  HttpServer::getInstance().chainWebApp(&goldbachWebApp);
  // Start the web server
  return  HttpServer::getInstance().start(argc, argv);
}

#endif  // WEBSERVER
