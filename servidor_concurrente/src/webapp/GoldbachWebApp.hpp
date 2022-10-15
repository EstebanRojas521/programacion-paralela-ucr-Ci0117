// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef GOLDBACHWEBAPP_HPP
#define GOLDBACHWEBAPP_HPP

#include <string>
#include <vector>
#include <csignal>

#include "HttpApp.hpp"
#include "HttpPackage.hpp"
#include "Producer.hpp"
#include "common.hpp"
//  #include Goldbach.hpp
#include "GoldbachResponder.hpp"


/**
@brief A web application that calculates prime factors
*/
class GoldbachWebApp : public HttpApp, public Producer<HttpPackage>{
  /// Objects of this class cannot be copied
  DISABLE_COPY(GoldbachWebApp);
  
 protected:

  GoldbachResponder goldbachResponder;

 public:
  /// Constructor
  GoldbachWebApp();

  /// Destructor
  ~GoldbachWebApp();

  /// Called by the web server when the web server is started
  void start() override;

  /// Called when the web server stops, in order cambio allow the web application
  /// clean up and finish as well
  void stop() override;

  /// Handle HTTP requests. @see HttpServer::handleHttpRequest()
  /// @return true If this application handled the request, false otherwise
  /// and another chained application should handle it

  bool handleHttpRequest(HttpRequest& HttpPackage);
  
 protected:

  /// Handle HTTP requests. @see HttpServer::handleHttpRequest()
  /// @return true If this application handled the request, false otherwise
  /// Sends the homepage as HTTP response
  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);
  /// Handle a HTTP request that starts with "/fact"
  /// @return true if the factorization was handled, false if it must be
  /// handled by another application
  bool serveFactorization(HttpRequest& httpRequest, HttpResponse& httpResponse);
  
  //  consume constantemente de la cola
  int run() override; 

  //  consume las solicitudes de la cola
  void consume(HttpRequest HttpPackage);

  //  Envia un paquete vacio para finalizar
  void detenerGoldbach();

  //  Envia un paquete vacio para finalizar las solicitudes
  void detenerSolicitudes();

  //  convertir string recibido a int
  bool convertStringToInt(std::string& number
  , int64_t& convertir);

    /**
   * @brief reemplazo de caracteres, se cambian por otro que
   * no aparece tan frecuente, y es facil de manipular
   * @param str la fila a ser reemplazada por
   * @param reemplazar la subfila para reemplazar
   * @param cambio subfila reemplazada
  */
  void reemplazoCaracteres(std::string& str,
    const std::string& reemplazar, const std::string& cambio);

    /** 
   * @brief Crea un vector que contiene a los numeros recibidos
   * @details El método asume que se ha pasado por la información
   * general (titulo) y continua "recolectando" los números que se
   * encuentras separados por el simbolo más, y por cada uno de ellos
   * los convierte en enteros, continua, mientras haya algo (número)
   * que procesar
   * @param URI recibe un strig
   * @param numbers vector que almacena números leídos
   * @param start inicio de la hilera
   * @param finish Fin de la hilera
   */
  void vectorNumeros(int start, int finish
  , const std::string URI, std::vector<int64_t>& numbers);
};

#endif  // FACTWEBAPP_HPP
