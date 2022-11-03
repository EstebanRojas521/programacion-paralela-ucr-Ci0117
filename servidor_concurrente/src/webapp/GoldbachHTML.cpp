// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#include "GoldbachHTML.hpp"
#include "SumGoldbachModel.hpp"
#include "common.hpp"

GoldbachHTML::GoldbachHTML() {}

GoldbachHTML::~GoldbachHTML() {}

void GoldbachHTML::validRequest(HttpPackage httpPackage) {
  httpPackage.httpResponse.setHeader
  ("Server", "AttoServer v1.0");
  httpPackage.httpResponse.setHeader
  ("Content-type", "text/html; charset=ascii");

  std::string title = "Sums of Goldbach of ";
  this->golbachElements.resize(httpPackage.numerosIngresados.size());
  int numbers_size = httpPackage.numerosIngresados.size();
  for (int i=0; i < numbers_size; i++) {
    // std::cout<<httpPackage.numerosIngresados[i]<<std::endl;
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

  // aca va donde llenamos el vector de golbach
  for (int i = 0; i < numbers_size; i++) {
    this->golbachElements[i].number = httpPackage.numerosIngresados[i];
    this->fillUpVector(this->golbachElements[i]);
  }
  this->goldbach_print(this->golbachElements, httpPackage.httpResponse);
  for (int i = 0; i < numbers_size; i++) {
    this->cleanUpVector(this->golbachElements[i]);
  }
  httpPackage.httpResponse.body()
  << "  <hr><p><a href=\"/\">Back</a></p>\n"
  << "</html>\n";
}


//podria pasar este metodo a golbach web app
void GoldbachHTML::invalidRequest(HttpPackage httpPackage) {
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


void GoldbachHTML::goldbach_print(std::vector<golbachElement> golbachElements, HttpResponse& httpResponse) {
  for (size_t i = 0; i < golbachElements.size(); i++) {
      if ((golbachElements[i].number%2) == 0) {
        print_even(golbachElements[i], httpResponse);
      } else {
        print_odd(golbachElements[i], httpResponse);
      }
      httpResponse.body() << "<h1>     </h1>\n";
  }
}


void GoldbachHTML::print_even(struct golbachElement goldbachStruct,
 HttpResponse& httpResponse) {
  size_t count = 0;
  size_t minusOne = -1;
  if (goldbachStruct.sizeOfVector != minusOne) {
      httpResponse.body() << goldbachStruct.number << ": "
      << goldbachStruct.sizeOfVector << " sums ";
      if (goldbachStruct.number < 0) {
        for (size_t j = 0; j < goldbachStruct.sizeOfVector; j++) {
          if ((j == 0) && (goldbachStruct.sizeOfVector != 1)) {
            httpResponse.body()
            << goldbachStruct.results[count] << "+"
            << goldbachStruct.results[count+1];
            } else {
            if ((j == (goldbachStruct.sizeOfVector-1))) {
              if (goldbachStruct.sizeOfVector == 1) {
                httpResponse.body()
                << goldbachStruct.results[count] << "+"
                << goldbachStruct.results[count+1];
              } else {
                httpResponse.body()
                << goldbachStruct.results[count] << "+"
                << goldbachStruct.results[count+1];
              }
            } else {
              httpResponse.body()
              << goldbachStruct.results[count] << "+"
              << goldbachStruct.results[count+1];
            }
          }
          count += 2;
          if ( j < goldbachStruct.sizeOfVector-1 ) {
            httpResponse.body() << ", ";
          }
        }
      }
    } else {
      httpResponse.body() << goldbachStruct.number << ": NA ";
    }
    httpResponse.body() << "\n";
}


void GoldbachHTML::print_odd(struct golbachElement goldbachStruct,
 HttpResponse& httpResponse) {
  size_t count = 0;
  // size_t minusOne = -1;
  if (goldbachStruct.number != -1) {
    httpResponse.body() << goldbachStruct.number << ": "
    << goldbachStruct.sizeOfVector << " sums";
    if (goldbachStruct.number < 0) {
      httpResponse.body() << ": ";
      for (size_t j = 0; j < goldbachStruct.sizeOfVector; j++) {
        if ((j == 0) && (goldbachStruct.sizeOfVector != 1)) {
          httpResponse.body()
          << goldbachStruct.results[count] << "+"
          << goldbachStruct.results[(count)+1] << "+"
          << goldbachStruct.results[(count)+2];
        } else {
          if ((j == (goldbachStruct.sizeOfVector-1))) {
            if (goldbachStruct.sizeOfVector == 1) {
              httpResponse.body()
              << goldbachStruct.results[count] << "+"
              << goldbachStruct.results[(count)+1] << "+"
              << goldbachStruct.results[(count)+2];
            } else {
              httpResponse.body()
              << goldbachStruct.results[count] << "+"
              << goldbachStruct.results[(count)+1] << "+"
              << goldbachStruct.results[(count)+2];
            }
          } else {
            httpResponse.body()
            << goldbachStruct.results[count] << "+"
            << goldbachStruct.results[(count)+1] << "+"
            << goldbachStruct.results[(count)+2];
          }
        }
        count += 3;
        if ( j < goldbachStruct.sizeOfVector-1 ) {
          httpResponse.body() << ", ";
        }
      }
    }
  } else {
    httpResponse.body() << goldbachStruct.number << ": NA";
  }
    httpResponse.body() << "\n";
}



void GoldbachHTML::fillUpVector(struct golbachElement& goldbachStruct) {
  size_t number = goldbachStruct.number;
  number = number;
  std::vector<size_t> results = goldbachStruct.results;
  SumGoldbachModel* sumGoldbachModel = new SumGoldbachModel();
  //sumGoldbachModel->processGoldbachNumber(goldbachStruct.number,
   //goldbachStruct.results);
  goldbachStruct.sizeOfVector = goldbachStruct.results.size();

  delete sumGoldbachModel;

  if (goldbachStruct.number % 2 == 0) {
    goldbachStruct.sizeOfVector = goldbachStruct.results.size()/2;
  } else {
    goldbachStruct.sizeOfVector = goldbachStruct.results.size()/3;
  }
}


void GoldbachHTML::cleanUpVector(struct golbachElement& goldbachStruct) {
  goldbachStruct.number = 0;
  goldbachStruct.results.clear();
  goldbachStruct.sizeOfVector = 0;
}
