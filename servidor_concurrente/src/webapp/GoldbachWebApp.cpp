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
  std::smatch matches;
  std::string URI = httpPackage.httpRequest.getURI();
  this->replaceCharacters(URI, std::string("%2C"), std::string("+"));
  std::cout<< URI <<std::endl;
  std::regex inQuery
  ("^/goldbach(/|\\?number=)(\\d+|\\-\\d+)(?:\\+(\\d+|\\-\\d+))*$");
  if (std::regex_search(URI, matches, inQuery)) {
    assert(matches.length() >= 3);
    int start = matches[1].length() == 1 ? 9 : 16;
    int finish = matches[0].length() - 1;
    this->createVectorOfNumbers
    (start, finish, URI, httpPackage.numerosIngresados);
    this->goldbachHTML.validRequest(httpPackage);
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

void GoldbachWebApp::createVectorOfNumbers(int start
, int finish, const std::string URI
, std::vector<int64_t>& numbers) {
  bool out_of_limit  = false;
  std::string number = "";
  for (int i = start + 1; i <= finish && !out_of_limit ; i++) {
    // std::cout<< start << std::endl;
    if (URI[i] != '+' && i != finish) {
      number += URI[i];
    } else {
      int64_t converted_number;
      if (i != finish) {
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

bool GoldbachWebApp::convertStringToInt(std::string& number
, int64_t& converted_number) {
  bool out_of_limit = false;
  try {
    converted_number = std::stoll(number);
  } catch (const std::out_of_range& out_of_range) {
    out_of_limit = true;
  }
  return out_of_limit;
}
