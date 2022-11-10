// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#ifndef HTTPCONNECTIONHANDLER_HPP
#define HTTPCONNECTIONHANDLER_HPP

#include <vector>
#include "Consumer.hpp"
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

class HttpConnectionHandler: public Consumer<Socket>{
  DISABLE_COPY(HttpConnectionHandler);

 protected:
  /// @brief Cantidad de sockets, 0 por defecto
  size_t numberOfSockets = 0;
  /// @brief Vector de tipo HttpApp
  std::vector<HttpApp*> applications;

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

 public:
  // HttpConnectionHandler();
  // ~HttpConnectionHandler();
  /**
   * @brief Constructor de HttpConnectionHandler
   * @param applications vector para inicializar el vector propio de la clase
   */
  explicit HttpConnectionHandler(std::vector<HttpApp*> applications);

  /**
   * @brief Metodo que llama a consumeForever()
   * @return int retorna EXIT_SUCCESS
   */
  int run() override;

  /**
   * @brief Metodo que consume sockets
   * @param client El socket a consumir
   */
  void consume(Socket client) override;
};

#endif
