// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <cassert>
#include <stdexcept>
#include <string>

#include "HttpApp.hpp"
#include "HttpServer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"
#include "Socket.hpp"
#include "Queue.hpp"

// TODO(you): Implement connection handlers argument
const char* const usage =
  "Usage: webserv [port] [handlers]\n"
  "\n"
  "  port        Network port to listen incoming HTTP requests, default "
    DEFAULT_PORT "\n"
  "  handlers     Number of connection handler theads\n";

//constructor
HttpServer::HttpServer() {
}


//destructor
HttpServer::~HttpServer() {
}

void HttpServer::listenForever(const char* port) {
  //metodo de la clase TCPServer
  return TcpServer::listenForever(port);
}

//acepta las solicitudes a todos
//solicitudes van atraves del http request
//este codigo es que hay que paralelizar
//TODO(you) va todo lo importante
//descargar extension to do
//servidor web = corre en hilo principal
//Persona que entra = va en cola = sockets
//cada socket =  representa una coneccion = representa una persona 
//conection handler = consumen los sockets = pero solo una vez
//crear arreglo de conection handlers
//conection handler, solo toman ordenes y mandan todas las solicitudes a una cola
//Procesa las solicitudes, hace golbach, y luego las despacha
//Clase conection handler no existe 
//Servidor web debe ser concurrente
//Romper la serialidad del codigo dado
//Route hay que cambiarlo porque actualmente lo hace el "guarda"
//Los codigos que desplegamos en la pagina van en HTTP(encabezado, cuerpo)
//
void HttpServer::handleClientConnection(Socket& client) {
  // TODO(you): Make this method concurrent. Store client connections (sockets)
  // into a collection (e.g thread-safe queue) and stop
  //Socket& newSocket = client;
  //client = client
  this->producingQueue->push(client);
  //std::cout<<"enter"<<std::endl;
  //client.close();
  // TODO(you) Move the following loop to a consumer thread class
  // While the same client asks for HTTP requests in the same connection
  // Consumer run sobrecargar -> el procesa el client
  //while (true) {
  //  // break;
  //   // Create an object that parses the HTTP request from the socket
  //   HttpRequest httpRequest(client);

  //   // If the request is not valid or an error happened
  //   if (!httpRequest.parse()) {
  //     // Non-valid requests are normal after a previous valid request. Do not
  //     // close the connection yet, because the valid request may take time to
  //     // be processed. Just stop waiting for more requests
  //     break;
  //   }

  //   // A complete HTTP client request was received. Create an object for the
  //   // server responds to that client's request
  //   HttpResponse httpResponse(client);

  //   // Give subclass a chance to respond the HTTP request
  //   const bool handled = this->handleHttpRequest(httpRequest, httpResponse);

  //   // If subclass did not handle the request or the client used HTTP/1.0
  //   if (!handled || httpRequest.getHttpVersion() == "HTTP/1.0") {
  //       std::cout<<"enter"<<std::endl;
  //     // The socket will not be more used, close the connection
  //     client.close();
  //     break;
  //   }

    // This version handles just one client request per connection
    // TODO(you): Remove this break after parallelizing this method
    //break;
  //}
  //std::cout<<"Number of clients: "<< this->producingQueue->returnQueQueCounter()<<std::endl;
}

void HttpServer::chainWebApp(HttpApp* application) {
  assert(application);
  this->applications.push_back(application);
}



int HttpServer::start(int argc, char* argv[]) {
  bool stopApps = false;
  try {
    if (this->analyzeArguments(argc, argv)) {
      // Start the log service
      //Es una bitacora que guardae eventos y los guarde en discos
      //Buena practica instaurar logs(bitacoras)
      Log::getInstance().start();

      // Start all web applications
      for (size_t index = 0; index < this->applications.size(); ++index) {
        this->applications[index]->start();
      }
      stopApps = true;

      // Start waiting for connections
      //Comienza a recibir solicitudes
      //Metodo de TCP server
      this->listenForConnections(this->port);
      const NetworkAddress& address = this->getNetworkAddress();
      Log::append(Log::INFO, "webserver", "Listening on " + address.getIP()
        + " port " + std::to_string(address.getPort()));

      // Accept all client connections
      //Acepta todas las conciciones que le mandan 
      //Solo acepta uno a la vez =  pero deberia de ser concurrente =  debe delegar tareas
      //servidor se encarga de la ventanilla, 
      //aplicaciones de los procesos -> golbach
      //HTTP = lenguje utilizado para comunicarse 
      //metodo heredado de TCPserver
      //codigo de red = no preocuparse
      //comienza a escuchar en un punto del sistema operativo -> se arma un socket
      this->producingQueue = new Queue<Socket>();
      //creamos 10 connection handler momentaneamente;
      this->consumers.resize(this->numberOfThreads);
      for ( size_t index = 0; index < this->numberOfThreads; ++index ) {
        this->consumers[index] = new HttpConnectionHandler(this->applications);
        assert(this->consumers[index]);
        this->consumers[index]->setConsumingQueue(this->producingQueue);
      }

      for ( size_t index = 0; index <this->numberOfThreads; ++index ) {
        this->consumers[index]->startThread();
      }
      this->acceptAllConnections();
      //Aqui terminamos todos los hilos -> creo

      for ( size_t index = 0; index <this->numberOfThreads; ++index ) {
        this->consumers[index]->waitToFinish();
      }
    }
    //catch donde verifica si no pudo conectarsea  un puerto
  } catch (const std::runtime_error& error) {
    std::cerr << "error: " << error.what() << std::endl;
  }

  // If applications were started
  if (stopApps) {
    // Stop web applications. Give them an opportunity to clean up
    for (size_t index = 0; index < this->applications.size(); ++index) {
      this->applications[index]->stop();
    }
  }

  // Stop the log service
  Log::getInstance().stop();

  return EXIT_SUCCESS;
}

bool HttpServer::analyzeArguments(int argc, char* argv[]) {
  // Traverse all arguments
  for (int index = 1; index < argc; ++index) {
    const std::string argument = argv[index];
    if (argument.find("help") != std::string::npos) {
      std::cout << usage;
      return false;
    }
  }

  if (argc >= 3) {
    this->port = argv[1];
    this->numberOfThreads = std::strtoull(argv[2], nullptr, 10);
  }
  else{
    //cantidad default de hilos es 10
    this->numberOfThreads = 10;
  }

  return true;
}

void HttpServer::stop() {
  // Stop listening for incoming client connection requests
  this->stopListening();
}
