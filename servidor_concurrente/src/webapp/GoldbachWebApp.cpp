// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <algorithm>
#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

#include "GoldbachHTML.hpp"
#include "HttpPackage.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "GoldbachWebApp.hpp"

GoldbachWebApp::GoldbachWebApp() {
}

GoldbachWebApp::~GoldbachWebApp() {
}

void GoldbachWebApp::start() {
  // TODO(you): Start producers, consumers, assemblers...
}

void GoldbachWebApp::stop() {
  // TODO(you): Stop producers, consumers, assemblers...
}


void GoldbachWebApp::consume(HttpPackage httpPackage) {
  this->handleHttpRequest(httpPackage);
}

bool GoldbachWebApp::handleHttpRequest(HttpPackage& httpPackage) {
  if (httpPackage.httpRequest.getMethod() == "GET" &&
  httpPackage.httpRequest.getURI() == "/") {
    return this->serveHomePage(httpPackage);
  }


  //aca no se deberia analizar ningun vector
  std::smatch matches;
  std::string URI = httpPackage.httpRequest.getURI();
  this->replaceCharacters(URI, std::string("%2C"), std::string("+"));
  std::cout<< URI <<std::endl;
  std::regex inQuery
  ("^/goldbach(/|\\?number=)(\\d+|\\-\\d+)(?:\\+(\\d+|\\-\\d+))*$");
  if (std::regex_search(URI, matches, inQuery)) {
    //aca pidieron golbach
    //tengo que llamar a serve golbach aca

    assert(matches.length() >= 3);
    int start = matches[1].length() == 1 ? 9 : 16;
    int finish = matches[0].length() - 1;
    //httpPackage.
    //serveGOlbach(start, finish,package);
    


    //aca llamamos a serve golbach ahora
    SumGoldbachModel* sumGoldbachModel = new SumGoldbachModel();

    //hasta aca esta bien
    sumGoldbachModel->serveGolbach(start,finish,httpPackage,URI);
  } else {
    httpPackage.solicitudInvalida = true;
    this->goldbachHTML.invalidRequest(httpPackage);
  }
  return EXIT_SUCCESS;
}

void GoldbachWebApp::replaceCharacters(std::string& str,
  const std::string& from, const std::string& to) {
  size_t position = 0;
  while ((position = str.find(from, position)) != std::string::npos)
  { str.replace(position, from.length(), to);
    position = position + to.length();
  }
}

bool GoldbachWebApp::serveHomePage(HttpPackage httpPackage) {
  // Set HTTP response metadata (headers)
  httpPackage.httpResponse.setHeader("Server", "AttoServer v1.1");
  httpPackage.httpResponse.setHeader("Content-type",
   "text/html; charset=ascii");
  // Build the body of the response
  std::string title = "Conjetura Goldbach";
  httpPackage.httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <style>body {font-family: monospace}</style>\n"
    << "  <h1>" << title << "</h1>\n"
    << "  <form method=\"get\" action=\"/goldbach\">\n"
    << "    <label for=\"number\">Numbers</label>\n"
    << "    <input type=\"text\" name=\"number\" required/>\n"
    << "    <button type=\"submit\">Calcular</button>\n"
    << "  </form>\n"
    << "</html>\n";

  // Send the response to the client (user agent)
  return httpPackage.httpResponse.send();
}

