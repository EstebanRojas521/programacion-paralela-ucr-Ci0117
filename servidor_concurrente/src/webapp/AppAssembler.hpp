// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#ifndef APPASSEMBLER_HPP
#define APPASSEMBLER_HPP

#include <vector>
#include "Consumer.hpp"
#include "Assembler.hpp"
#include "AppAssembler.hpp"
#include "Socket.hpp"
#include "TcpServer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "HttpConnectionHandler.hpp"
#include "Queue.hpp"
#include "HttpServer.hpp"
#include "HttpApp.hpp"
#include "HttpPackage.hpp"
#include "GoldbachStruct.hpp"



class AppAssembler: public Assembler<GoldbachStruct, GoldbachStruct>{
  // talvez haya que poner referencia
  HttpPackage& package;

 public:
  /**
   * @brief Constructor de AppAssembler
   * @param httpPackage HttpPackage a inicializar
   */
  explicit AppAssembler(HttpPackage& httpPackage);

  /**
   * @brief Metodo heredado que llama a consumeForever
   * @return int retorna 0
   */
  int run() override;

  /**
   * @brief Metodo que consume datos de tipo GoldbachStruct y los envia a imprimir
   * @param data GoldbachStruct a imprimir
   */
  void consume(GoldbachStruct data) override;

  /**
   * @brief Metodo que imprime las sumas de goldbach para un numero par
   * @param data GoldbachStruct que contiene el numero y sus sumas
   */
  void print_even(GoldbachStruct data);

  /**
   * @brief Metodo que imprime las sumas de goldbach para un numero impar
   * @param data GoldbachStruct que contiene el numero y sus sumas
   */
  void print_odd(GoldbachStruct data);

  /**
   * @brief Metodo que imprime las sumas de goldbach para un numero 
   * @param data GoldbachStruct que contiene el numero y sus sumas
   */
  void goldbach_print(GoldbachStruct data);
};

#endif
