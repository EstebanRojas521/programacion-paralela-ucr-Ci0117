// Copyright 2021 James Araya, Gabriel González,
// David Obando. Universidad de Costa Rica. CC BY 4.0

#include "HttpPackage.hpp"

HttpPackage::HttpPackage(const HttpRequest& httpRequest,
  const HttpResponse& httpResponse, bool stopCondition)
  : httpRequest(httpRequest), httpResponse(httpResponse)
  , condicionParada(stopCondition) {
    this->solicitudInvalida = false;
}

HttpPackage::~HttpPackage() {
}

bool HttpPackage::operator==(const HttpPackage httpPackage) const {
  return (this->condicionParada == httpPackage.condicionParada);
}
