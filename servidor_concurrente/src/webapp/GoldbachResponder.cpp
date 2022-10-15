//2022 CY

#include "GoldbachResponder.hpp"
#include "common.hpp"

//GoldbachResponder::GoldbachResponder()
 // : Consumer(true) {}


GoldbachResponder::GoldbachResponder(){}

GoldbachResponder::~GoldbachResponder(){}

//int GoldbachResponder::run() {
  //this->consumeForever();
  //return EXIT_SUCCESS;
//}


void GoldbachResponder::validRequest(HttpPackage httpPackage) {
  httpPackage.httpResponse.setHeader
  ("Server", "AttoServer v1.0");
  httpPackage.httpResponse.setHeader
  ("Content-type", "text/html; charset=ascii");

  std::string title = "Sums of Goldbach of ";

  int numbers_size = httpPackage.numerosIngresados.size();
  for (int i=0; i < numbers_size; i++) {
    //std::cout<<httpPackage.numerosIngresados[i]<<std::endl;
    title += std::to_string(httpPackage.numerosIngresados[i]);
    if (i+1 == numbers_size) {
      break;
    }
    title += ',';
  }

  httpPackage.httpResponse.body() << "<!DOCTYPE html>\n"
  << "  <html lang=\"en\">\n"
  << "  <meta charset=\"ascii\"/>\n"
  << "  <title>" << title << "</title>\n"
  << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
  << "  <h1>" << title << "</h1>\n";

  //goldbach_print(httpPackage.results, httpPackage.httpResponse);

  httpPackage.httpResponse.body()
  << "  <hr><p><a href=\"/\">Back</a></p>\n"
  << "</html>\n";
}

void GoldbachResponder::invalidRequest(HttpPackage httpPackage) {
  std::string title = "Invalid Request in Sums of Goldbach";
  httpPackage.httpResponse.body() << "<!DOCTYPE html>\n"
        << "<html lang=\"en\">\n"
        << "  <meta charset=\"ascii\"/>\n"
        << "  <title>" << title << "</title>\n"
        << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
        << "  <h1 class=\"err\">" << title << "</h1>\n"
        << "  <p>Invalid request for sums of Goldbach</p>\n"
        << "  <hr><p><a href=\"/\">Back</a></p>\n"
        << "</html>\n";
}



