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

class HttpApp;
class HttpServer;


class HttpAssembler: public Assembler<Socket>{
 protected:
  std::vector<HttpApp*> applications;

 public:
  HttpAssembler();

  int run() override;

  void consumeASBM(Socket client) override;

  explicit HttpAssembler(std::vector<HttpApp*> applications);

  /**
   * @brief Metodo que maneja un request Http
   * @param httpPackage Package de donde saca IP y puerto
   */
  virtual bool handleHttpRequest(HttpPackage& httpPackage);

  /**
   * @brief Metodo que establece si las aplicaciones manejan un package
   * @param httpPackage Package a manejar
   */
  bool route(HttpPackage& httpPackage);

  /**
   * @brief Mensaje que se imprime en caso de no encontrar el servidor
   * @param httpPackage Paquete para fijar informacion de error
   */
  bool serveNotFound(HttpPackage& httpPackage);
};

#endif
