// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#include <string>
#include "HttpConnectionHandler.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"

// constructor
HttpConnectionHandler::HttpConnectionHandler(std::vector<HttpApp*> applications)
  : applications(applications) {
}

// HttpConnectionHandler::~HttpConnectionHandler(){

// }


int HttpConnectionHandler::run() {
  this->consumeForever();
  // Log::append(Log::INFO, "Consumer", std::to_string(this->numberOfSockets)
  // + " Sockets consumed");
  return EXIT_SUCCESS;
}


void HttpConnectionHandler::consume(Socket client) {
   while (true) {
    // break;
    // Create an object that parses the HTTP request from the socket
    HttpRequest httpRequest(client);
    // If the request is not valid or an error happened
    if (!httpRequest.parse()) {
      // Non-valid requests are normal after a previous valid request. Do not
      // close the connection yet, because the valid request may take time to
      // be processed. Just stop waiting for more requests
      break;
    }

    // A complete HTTP client request was received. Create an object for the
    // server responds to that client's request
    HttpResponse httpResponse(client);

    std::vector<int64_t> numerosIngresados;
    // HttpPackage httpPackage(httpRequest, httpResponse,nullptr,false);
    // Give subclass a chance to respond the HTTP request
    HttpPackage package(httpRequest, httpResponse,"/goldbach" ,numerosIngresados, false);
    const bool handled = this->handleHttpRequest(package);
    // If subclass did not handle the request or the client used HTTP/1.0
    if (!handled || httpRequest.getHttpVersion() == "HTTP/1.0") {
      std::cout << "enter" << std::endl;
      // The socket will not be more used, close the connection
      client.close();
      break;
    }
    // This version handles just one client request per connection
    // TODO(you): Remove this break after parallelizing this method
    // break;
  }
}

//
bool HttpConnectionHandler::handleHttpRequest(HttpPackage& httpPackage) {
  // Print IP and port from client
  const NetworkAddress& address = httpPackage.httpRequest.getNetworkAddress();
  Log::append(Log::INFO, "connection",
    std::string("connection established with client ") + address.getIP()
    + " port " + std::to_string(address.getPort()));

  // Print HTTP request
  Log::append(Log::INFO, "request", httpPackage.httpRequest.getMethod()
    + ' ' + httpPackage.httpRequest.getURI()
    + ' ' + httpPackage.httpRequest.getHttpVersion());


  //aca llamamos al dispathcer -> es como un produce 
  std::cout<< "Im on connection handler, just pushed package" <<std::endl;
  this->produce(httpPackage);
  //this->produce(HttpPackage());
  //no estoy seguro si debe retornar algo, talvez es un metodo void
  return true;
  //return this->route(httpPackage);
}
