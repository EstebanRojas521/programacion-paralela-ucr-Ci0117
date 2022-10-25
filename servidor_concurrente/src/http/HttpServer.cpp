// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <cassert>
#include <stdexcept>
#include <string>
#include <csignal>

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


//destructor = defaulted
//HttpServer::~HttpServer() {}


HttpServer& HttpServer::getInstance(){
  static HttpServer server;
  return server;
}

void HttpServer::listenForever(const char* port) {
  //metodo de la clase TCPServer
  return TcpServer::listenForever(port);
}

void HttpServer::handleClientConnection(Socket& client) {
  this->producingQueue->push(client);
}

void HttpServer::chainWebApp(HttpApp* application) {
  assert(application);
  this->applications.push_back(application);
}


void signal_handler(int signal_num)
{
  signal_num = signal_num;
  // std::cout << "The interrupt signal is (" << signal_num
  //     << "). \n";

  HttpServer::getInstance().stop();
  // It terminates the  program
  //exit(signal_num);
}


int HttpServer::start(int argc, char* argv[]) {
  bool stopApps = false;
  signal(SIGINT, signal_handler);  
  try {
    //signal(SIGINT, signal_handler);  
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
    }
    //catch donde verifica si no pudo conectarsea  un puerto
  } catch (const std::runtime_error& error) {
    // this->stop();
    //se encicla porque los hilos no terminan (no se como hacerlos terminar)
    for ( size_t index = 0; index <this->numberOfThreads; ++index ) {
      //Thread::~thread(this->consumers[index]);
      this->producingQueue->push(Socket());
    }
    for ( size_t index = 0; index <this->numberOfThreads; ++index ) {
      this->consumers[index]->waitToFinish();
    }
    for ( size_t index = 0; index <this->numberOfThreads; ++index ) {
      delete this->consumers[index];
    }
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
  std::cout<<"SERVER STOPED"<<std::endl;
  // Stop listening for incoming client connection requests
  this->stopListening();
}




