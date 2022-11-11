
// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#ifndef HTTPPACKAGE_H
#define HTTPPACKAGE_H
#include <inttypes.h>
#include <vector>
#include <cstdint>
#include "common.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Socket.hpp"

struct  HttpPackage{
 public:
  /// Request de cada package
  HttpRequest httpRequest;
  /// Response de cada package
  HttpResponse httpResponse;
  /// Vector de numeros ingresados por el usuario
  std::vector<int64_t> numerosIngresados;
  // Agregar vector para resultados
  // resultado de la clase Goldbach std::vector<resultados> results;
  bool solicitudInvalida = false;

 public:
  /**
   * @brief Constructor de la clase HttpPackage
   * @param httpRequest Request a inicializar
   * @param httpResponse Response a inicializar
   * @param numerosIngresados vector de numeros inicializados en 0
   * @param solicitudInvalida variable booleana, falsa por defecto
   */
  HttpPackage(HttpRequest httpRequest = HttpRequest(),
               HttpResponse httpResponse = HttpResponse(),
                std::vector<int64_t> numerosIngresados = {0},
                 bool solicitudInvalida = false)
    : httpRequest(httpRequest)
    , httpResponse(httpResponse)
    , numerosIngresados(numerosIngresados)
    , solicitudInvalida(solicitudInvalida) {}

  /**
   * @brief Sobrecarga de operador de igualdad, compara HttpPackages
   * @param other El HttpPackage a comparar con si mismo
   * @return true Si son iguales
   * @return false Si son diferentes
   */
  inline bool operator==(const HttpPackage& other) const {
    return this->httpRequest == other.httpRequest
      && this->httpResponse == other.httpResponse
      && this->solicitudInvalida == other.solicitudInvalida;
  }

  // HttpPackage(){}
};

#endif
