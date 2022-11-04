// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#include "HttpPackage.hpp"

HttpPackage::HttpPackage(const HttpRequest& httpRequest,
 const HttpResponse& httpResponse)
  : httpRequest(httpRequest), httpResponse(httpResponse) {
    this->solicitudInvalida = false;
}

HttpPackage::~HttpPackage() {
}
