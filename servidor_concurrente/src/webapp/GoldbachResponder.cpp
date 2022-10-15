// #include "GoldbachResponder.hpp"
// #include "common.hpp"

// void GoldbachResponder::consume(HttpPackage httpPackage) {
//   if (httpPackage.solicitudInvalida) {
//     this->solicitudInvalida(httpPackage);
//   } else {
//     this->solicitudValida(httpPackage);
//   }
//   bool handled = httpPackage.httpResponse.send();
//   if (!handled) {
//     httpPackage.httpResponse.getSocket().close();
//   }
// }

// void GoldbachResponder::solicitudInvalida(HttpPackage httpPackage) {
//   std::string titulo = "Solicitud invalida";
//   httpPackage.httpResponse.body() << "<!DOCTYPE html>\n"
//         << "<html lang=\"en\">\n"
//         << "  <meta charset=\"ascii\"/>\n"
//         << "  <title>" << titulo << "</title>\n"
//         << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
//         << "  <h1 class=\"err\">" << titulo << "</h1>\n"
//         << "  <p>Invalid request for sums of Goldbach</p>\n"
//         << "  <hr><p><a href=\"/\">Back</a></p>\n"
//         << "</html>\n";
// }

// void GoldbachResponder::solicitudValida(HttpPackage httpPackage) {
//   httpPackage.httpResponse.setHeader
//   ("Server", "AttoServer v1.0");
//   httpPackage.httpResponse.setHeader
//   ("Content-type", "text/html; charset=ascii");

// //  Agrega los números leídos al título
//   std::string titulo = "Conjetura de Goldbach ";

//   int tamano = httpPackage.numerosIngresados.size();
//   for (int i=0; i < tamano; i++) {
//     titulo += std::to_string(httpPackage.numerosIngresados[i]);
//     if (i+1 == tamano) {
//       break;
//     }
//     titulo += ',';
//   }

//     httpPackage.httpResponse.body() << "<!DOCTYPE html>\n"
//   << "  <html lang=\"en\">\n"
//   << "  <meta charset=\"ascii\"/>\n"
//   << "  <title>" << titulo << "</title>\n"
//   << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
//   << "  <h1>" << titulo << "</h1>\n";

//   //goldbach_print(httpPackage.results, httpPackage.httpResponse);

//   httpPackage.httpResponse.body()
//   << "  <hr><p><a href=\"/\">Back</a></p>\n"
//   << "</html>\n";
// }

