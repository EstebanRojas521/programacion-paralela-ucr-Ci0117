#include "HttpPackage.hpp"

HttpPackage::HttpPackage(const HttpRequest& httpRequest,
  const HttpResponse& httpResponse)
  : httpRequest(httpRequest), httpResponse(httpResponse){
    this->solicitudInvalida = false;
}

HttpPackage::~HttpPackage() {
}
