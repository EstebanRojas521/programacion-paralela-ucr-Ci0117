
// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#ifndef HTTPPACKAGE_H
#define HTTPPACKAGE_H
#include <inttypes.h>
#include <vector>
#include "common.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"


struct  HttpPackage{
  public:
  /// Request de cada package
  HttpRequest httpRequest ;
  /// Response de cada package
  HttpResponse httpResponse;
  /// Vector de numeros ingresados por el usuario
  std::vector<int64_t> numerosIngresados;
  // Agregar vector para resultados
  // resultado de la clase Goldbach std::vector<resultados> results;
  bool solicitudInvalida = false;

 public:
  HttpPackage( HttpRequest httpRequest, HttpResponse httpResponse,
  std::vector<int64_t> numerosIngresados, bool solicitudInvalida)
  : httpRequest(httpRequest)
  ,httpResponse(httpResponse)
  ,numerosIngresados(numerosIngresados)
  ,solicitudInvalida(solicitudInvalida) {}

  //HttpPackage(){}
};



#endif
