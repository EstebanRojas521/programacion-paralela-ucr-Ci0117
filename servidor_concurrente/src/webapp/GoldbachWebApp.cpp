// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <algorithm>
#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

#include "GoldbachWebApp.hpp"
#include "HttpPackage.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

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


void GoldbachWebApp::createVectorOfNumbers(int start, int finish,
                const std::string URI, std::vector<int64_t>& numbers) {
    bool out_of_limit  = false;
    std::string number = "";
    for (int i = start + 1; i <= finish && !out_of_limit ; i++) {
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
            } else {
                number += URI[i];
                out_of_limit  = convertStringToInt(number, converted_number);
                if (!out_of_limit) {
                    numbers.push_back(converted_number);
                }
            }
        }
    }
}

bool GoldbachWebApp::convertStringToInt(std::string& number,
                                            int64_t& converted_number) {
    bool out_of_limit = false;
    try {
        converted_number = std::stoll(number);
    } catch (const std::out_of_range& out_of_range) {
        out_of_limit = true;
    }
    return out_of_limit;
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
    std::vector<SumGoldbachModel*> producers;
    AppAssembler* assembler = new AppAssembler(httpPackage);
    AppAssembler* fakeAssembler = new AppAssembler(httpPackage);
    fakeAssembler->createOwnQueueASBM();
    assembler->createOwnQueueASBM();
    assert(matches.length() >= 3);
    int start = matches[1].length() == 1 ? 9 : 16;
    int finish = matches[0].length() - 1;
    // httpPackage.
    // serveGOlbach(start, finish,package);
    //creamos vector de numeros
    this->createVectorOfNumbers(start, finish, URI,
    httpPackage.numerosIngresados);
    producers.resize(httpPackage.numerosIngresados.size());
    // aca llamamos al equipo trabajor de hilos
    // que regresan? los resultados, pero en que forma?
    //SumGoldbachModel* sumGoldbachModel = new SumGoldbachModel();
    // aca creamos un hilo para cada numero de httpPackage.numerosIngresados
    // regresan un golbach struct que se pone en cola para el assembler
    int size = httpPackage.numerosIngresados.size();
    bool verdadero = true;
    bool falso = false;
    if(size == 1){
      producers[0] = new SumGoldbachModel(httpPackage.numerosIngresados[0],verdadero,verdadero);
    }
    else if(size == 2){
      producers[0] = new SumGoldbachModel(httpPackage.numerosIngresados[0],verdadero,falso);
      producers[1] = new SumGoldbachModel(httpPackage.numerosIngresados[1],falso,verdadero);
    }
    else{
      for(int i  = 0 ; i < size; i++){
        int number = httpPackage.numerosIngresados[i];
        int verdadero = 1;
        int falso = 0;
        if(i == 0){
          producers[i] = new SumGoldbachModel(number,verdadero,falso);
        }
        if(i != size-1&&i!=0){
          //std::cout<<number<<std::endl;
          producers[i] = new SumGoldbachModel(number,falso,falso);
        }
        else if(i!=0){ 
          //el el ultimo, queremos que se detenga
          producers[i] = new SumGoldbachModel(number,falso,verdadero);
        }
      }
    }
    for(int i  = 0 ; i < size; i++){
      producers[i]->setProducingQueue(assembler->getConsumingQueueASBM());
    }

    for(int i  = 0 ; i < size; i++){
      producers[i]->startThread();
    }
    assembler->setProducingQueueASBM(fakeAssembler->getConsumingQueueASBM());
    assembler->startThread();
    assembler->waitToFinish();
  } else {
    httpPackage.solicitudInvalida = true;
    this->invalidRequest(httpPackage);
  }
  return EXIT_SUCCESS;
}

void GoldbachWebApp::replaceCharacters(std::string& str,
  const std::string& from, const std::string& to) {
  size_t position = 0;
  while ((position = str.find(from, position)) != std::string::npos) {
    str.replace(position, from.length(), to);
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

void GoldbachWebApp::invalidRequest(HttpPackage httpPackage) {
  std::string title = "Invalid Request in Sums of Goldbach";
  httpPackage.httpResponse.body() << "<!DOCTYPE html>\n"
  << "<html lang=\"en\">\n"
  << "  <meta charset=\"ascii\"/>\n"
  << "  <title>" << title << "</title>\n"
  << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
  << "  <h1 class=\"err\">" << title << "</h1>\n"
  << "  <p>Invalid request for sums of Goldbach</p>\n"
  << "  <hr><p><a href=\"/\">Back</a></p>\n"
  << "</html>\n";
}


int GoldbachWebApp::run(){
  return 0;
};


