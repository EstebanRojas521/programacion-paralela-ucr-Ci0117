// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#include "HttpDispatcher.hpp"


HttpDispatcher::HttpDispatcher(){}

int HttpDispatcher::run(){ 
    std::cout << "Im on dispatcher" <<std::endl;   
    this->consumeForever();
    for (const auto& pair : this ->toQueues){
       pair.second -> push(HttpPackage());
    }
    return EXIT_SUCCESS;
}  


std::string HttpDispatcher::extractKey( HttpPackage& package){
    if(package.key == "/goldbach"){
        std::cout << "Key was correct" <<std::endl;   
        return package.key;
    }
    else{
        serveNotFound(package);
    }
    return "";
}


bool HttpDispatcher::serveNotFound(HttpPackage& httpPackage) {
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



