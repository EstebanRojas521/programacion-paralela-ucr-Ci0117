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
  // ahora no consume, las pone en cola para el http assembler
  // pushea client a una cola
  this->producingQueue = new Queue<Socket>();

  // this->assembler->createOwnQueueASBM();
  this->assembler = new HttpAssembler(applications);
  this->assembler->setConsumingQueueASBM(this->producingQueue);
  this->producingQueue->push(client);
  this->assembler->startThread();

  // aca creamos los hilos de httapss que son assemblers tambien
  // consumen los packages -> producen los packages

  // aca talvez va el empaquetador?

  // wait to finish probablemente se encicle porque no
  // hay condicion de parada
  // this->assembler->waitToFinish();
}
