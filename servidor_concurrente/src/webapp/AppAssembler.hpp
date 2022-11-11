// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#ifndef APPASSEMBLER_HPP
#define APPASSEMBLER_HPP

#include <vector>
#include "Consumer.hpp"
#include "Assembler.hpp"
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

class AppAssembler: public Assembler<GoldbachStruct>{
  // talvez haya que poner referencia
  HttpPackage& package;

 public:
  explicit AppAssembler(HttpPackage& httpPackage);
  int run() override;
  void consumeASBM(GoldbachStruct data) override;

  /**
   * @brief Imprimime los resultados de la suma de Goldbach cuando
   * los datos son válidos. Imprime resultados para números pares
   * @param goldbachStruct contiene lnumberos resultados
   * @param httpResponse envia la respuesta al usuario.
   */
  void print_even(GoldbachStruct data);

  /**
   * @brief Imprimime los resultados de la suma de Goldbach cuando
   * los datos son válidos. Imprime resultados para números impares
   * @param goldbachStruct ontiene los resultados
   * @param httpResponse envia la respuesta al usuario.
   */
  void print_odd(GoldbachStruct data);

  /**
   * @brief Llamado general a imprimir los resultados
   * se divide acorde a la conjetura, débil o fuerte
   * @param goldbachStruct Arreglo con todos los resultados obtenidos
   * de los números ingresados.
   * @param httpResponse muestra los resultados al usuario
   */
  void goldbach_print(GoldbachStruct data);
};

#endif
