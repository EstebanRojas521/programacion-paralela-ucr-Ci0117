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
    HttpPackage httpPackage(httpRequest, httpResponse);
    // Give subclass a chance to respond the HTTP request
    const bool handled = this->handleHttpRequest(httpPackage);
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

  return this->route(httpPackage);
}


bool HttpConnectionHandler::route(HttpPackage& httpPackage) {
  // Traverse the chain of applications
  // bool entered = true;
  for (size_t index = 0; index < this->applications.size(); ++index) {
    // If this application handles the request
    HttpApp* app = this->applications[index];
    if (app->handleHttpRequest(httpPackage)) {
      return true;
    }
  }

  // Unrecognized request
  return this->serveNotFound(httpPackage);
  // return true;
}


bool HttpConnectionHandler::serveNotFound(HttpPackage& httpPackage) {
  // (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpPackage.httpResponse.setStatusCode(404);
  httpPackage.httpResponse.setHeader("Server", "AttoServer v1.1");
  httpPackage.httpResponse.setHeader("Content-type",
  "text/html;charset=ascii");

  // Build the body of the response
  std::string title = "Not found";
  httpPackage.httpResponse.body() << "<!DOCTYPE html>\n"
  << "<html lang=\"en\">\n"
  << "  <meta charset=\"ascii\"/>\n"
  << "  <title>" << title << "</title>\n"
  << "  <style>body {font-family: monospace} h1 {color: red}</style>\n"
  << "  <h1>" << title << "</h1>\n"
  << "  <p>The requested resouce was not found on this server.</p>\n"
  << "  <hr><p><a href=\"/\">Homepage</a></p>\n"
  << "</html>\n";

  // httpPackage.httpResponse.body() << "<!DOCTYPE html>\n"
  // Send the response to the client (user agent)
  return httpPackage.httpResponse.send();
}
