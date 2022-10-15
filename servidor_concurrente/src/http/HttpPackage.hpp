

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
  // resultado de la clase Goldbach std::vector<resultados> results;
  bool solicitudInvalida;

  /**
  @brief Paquete de datos (unifica) con requests and response 
  @param httpRequest request 
  @param httpResponse response
  */
  explicit HttpPackage(const HttpRequest& httpRequest,
   const HttpResponse& httpResponse);

  /**
  @brief Destructor.
  */
  ~HttpPackage();

};

#endif
