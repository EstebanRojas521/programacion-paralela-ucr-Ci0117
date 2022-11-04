// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef HTTPSERVER_H
#define HTTPSERVER_H
#include <csignal>
#include <vector>

#include "TcpServer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "HttpConnectionHandler.hpp"
#include "Queue.hpp"
#include "Socket.hpp"
#define DEFAULT_PORT "8080"

class HttpApp;
class HttpConnectionHandler;
// Notas - tema15
// los puertos se puede ver como direcciones de telefono,
// donde buscamos contactarlo con alguien
// (en este caso el servidor)
// delega control a las aplicaciones
// TODO(cualquiera): Documentation
// TCP server =  servidor seguro
class HttpServer: public TcpServer {
  DISABLE_COPY(HttpServer);

 private:
  HttpServer();
  /// Destructor
  ~HttpServer() = default;
  Queue<Socket>* producingQueue;
  std::vector<HttpConnectionHandler*>consumers;
  int indexConnectionHandlers;

  // cual es la diferencia entre protected y private
 protected:
  /// Lookup criteria for searching network information about this host
  struct addrinfo hints;
  /// TCP port where this web server will listen for connections

  const char* port = DEFAULT_PORT;
  size_t numberOfThreads  = 0;
  /// Chain of registered web applications. Each time an incoming HTTP request
  /// is received, the request is provided to each application of this chain.
  /// If an application detects the request is for it, the application will
  /// call the httpResponse.send() and the chain stops. If no web app serves
  /// the request, the not found page will be served.

  // vector de punteros a las aplicaciones
  std::vector<HttpApp*> applications;

 public:
  static HttpServer& getInstance();
  /// Constructor
  // HttpServer();
  /// Destructor
  // ~HttpServer();
  /// Registers a web application to the chain
  void chainWebApp(HttpApp* application);
  /// Start the web server for listening client connections and HTTP requests
  int start(int argc, char* argv[]);

  // static void signalHandler();
  /// Stop the web server. The server may stop not immediately. It will stop
  /// for listening further connection requests at once, but pending HTTP
  /// requests that are enqueued will be allowed to finish
  void stop();
  /// Infinetelly listen for client connection requests and accept all of them.
  /// For each accepted connection request, the virtual onConnectionAccepted()
  /// will be called. Inherited classes must override that method
  void listenForever(const char* port);

  // protected:
  /// Analyze the command line arguments
  /// @return true if program can continue execution, false otherwise
  bool analyzeArguments(int argc, char* argv[]);
  /// This method is called each time a client connection request is accepted.
  void handleClientConnection(Socket& client) override;
  /// Called each time an HTTP request is received. Web server should analyze
  /// the request object and assemble a response with the response object.
  /// Finally send the response calling the httpResponse.send() method.
  /// @return true on success and the server will continue handling further
  /// HTTP requests, or false if server should stop accepting requests from
  /// this client (e.g: HTTP/1.0)
};

#endif  // HTTPSERVER_H
