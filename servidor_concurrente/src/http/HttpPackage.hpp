// Copyright 2022 #Agregar nombres Universidad de Costa Rica. CC BY 4.0

#ifndef HTTPPACKAGE_H
#define HTTPPACKAGE_H

#include <inttypes.h>
#include <vector>

#include "common.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

class HttpPackage {
 public:
  /// Objects of this class can be copied, but avoid innecesary copies
  DECLARE_RULE4(HttpPackage, default);

  HttpRequest httpRequest;
  HttpResponse httpResponse;
  std::vector<int64_t> numerosIngresados;
  //  Agregar vector para resultados
  // resultado de la clase Goldbach std::vector<result> results;
  bool solicitudInvalida;
  bool condicionParada;

  /**
  @brief Paquete de datos (unifica) con requests and response 
  @param httpRequest request 
  @param httpResponse response
  @param condicionParada condición de parada para el programa
  */
  explicit HttpPackage(const HttpRequest& httpRequest,
   const HttpResponse& httpResponse
    , bool condicionParada = true);

  /**
  @brief Destructor.
  */
  ~HttpPackage();
  bool operator==(const HttpPackage httpPackage) const;
};

#endif
