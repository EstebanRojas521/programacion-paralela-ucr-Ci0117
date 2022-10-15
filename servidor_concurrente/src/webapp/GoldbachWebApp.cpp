// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <algorithm>
#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

#include "GoldbachWebApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "HttpPackage.hpp"

GoldbachWebApp::GoldbachWebApp() : HttpApp()
, Producer(new Queue<HttpPackage>) {
}

GoldbachWebApp::~GoldbachWebApp() {
  delete this->getProducingQueue();
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
  // If the home page was asked
  std::smatch matches;
  std::string URI = httpPackage.httpRequest.getURI();
  this->reemplazoCaracteres(URI, std::string("%2C"), std::string("+"));
  std::regex inQuery
  ("^/goldbach(/|\\?number=)(\\d+|\\-\\d+)(?:\\+(\\d+|\\-\\d+))*$");
  if (std::regex_search(URI, matches, inQuery)) {
    assert(matches.length() >= 3);
    int inicio = matches[1].length() == 1 ? 9 : 16;
    int fin = matches[0].length() - 1;
    this->vectorNumeros
    (inicio, fin, URI, httpPackage.numerosIngresados);
  } else {
    httpPackage.solicitudInvalida = true;
  }
  this->produce(httpPackage);
  return EXIT_SUCCESS;
}

// TODO(you): Fix code redundancy in the following methods

bool GoldbachWebApp::serveHomepage(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.1");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Conjetura Goldbach";
  httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <style>body {font-family: monospace}</style>\n"
    << "  <h1>" << title << "</h1>\n"
    << "  <form method=\"get\" action=\"/fact\">\n"
    << "    <label for=\"number\">Number</label>\n"
    << "    <input type=\"number\" name=\"number\" required/>\n"
    << "    <button type=\"submit\">Goldbach</button>\n"
    << "  </form>\n"
    << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}

//  aplica la línea 102
void GoldbachWebApp::reemplazoCaracteres(std::string& str,
  const std::string& from, const std::string& to) {
  size_t position = 0;
  while ((position = str.find(from, position)) != std::string::npos)
  { str.replace(position, from.length(), to);
    position = position + to.length();
  }
}

//  crea un vector de números
void GoldbachWebApp::vectorNumeros(int inicio
, int fin, const std::string URI
, std::vector<int64_t>& numbers) {
  bool out_of_limit  = false;
  std::string number = "";
  for (int i = inicio + 1; i <= fin && !out_of_limit ; i++) {
    if (URI[i] != '+' && i != fin) {
      number += URI[i];
    } else {
      int64_t converted_number;
      if (i != fin) {
        out_of_limit = convertStringToInt(number, converted_number);
        if (!out_of_limit) {
          numbers.push_back(converted_number);
          number = "";
        }
      } else { number += URI[i];
        out_of_limit  = convertStringToInt(number, converted_number);
        if (!out_of_limit) {
        numbers.push_back(converted_number);
        }
      }
    }
  }
}