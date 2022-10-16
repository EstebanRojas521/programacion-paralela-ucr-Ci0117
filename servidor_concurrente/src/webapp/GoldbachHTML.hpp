
#ifndef GOLDBACHHTML_H
#define GOLDBACHHTML_H

#include <string>
#include <vector>

#include "common.hpp"
#include "Consumer.hpp"
#include "HttpPackage.hpp"

 /**
  * @brief Creates the response that it's send to the user.
  */
 
class GoldbachHTML{
  DISABLE_COPY(GoldbachHTML);



  //algunos de estos metodos pueden ser protegidos
  public:

 /**
  * @brief elementos utilizados por Goldbach
  * @param number numeros recibidos por Goldbach
  * @param sizeOfVector tamaño del vector
  * @param results recibe los resultados de Goldbach
  */
  struct golbachElement{
    int number;
    size_t sizeOfVector;
    //el tipo de dato puede cambiar(no se como funciona golbach) 
    std::vector<size_t> results;
  };
  /**
  * @brief Default constructor.
  */
  GoldbachHTML();
  ~GoldbachHTML();

  /**
  * @brief Verifica si los datos dados por el usuario son válidos
  * @details Si la información es válida, se procesa, es decir,
  * se recibe, se pasa al vector y se ejecuta Goldbach
  * @param httpPackage paquete de solicitudes y respuestas
  */
  void validRequest(HttpPackage httpPackage);


  std::vector<golbachElement> golbachElements;

  /**
  * @brief llena el vector con los resultados de las
  * sumas de Goldbach
  * @param goldbachStruct struct de Goldbach
  */
  void fillUpVector(struct golbachElement& goldbachStruct);

  /**
  * @brief Limpia el arreglo con los resultados de Goldbach
  * @details envia un "paquete" con elementos en 0
  * @param goldbachStruct struct de Goldbach
  */
  void cleanUpVector(struct golbachElement& goldbachStruct);

  /**
  * @brief Si los datos no son válidos, se ingresa a este método
  * @details se retorna un mensaje de error cuando los datos dados
  * son inválidos
  * @param httpPackage paquete de solicitudes y respuestas
  */
  void invalidRequest(HttpPackage httpPackage);

  /**
  * @brief Imprimime los resultados de la suma de Goldbach cuando
  * los datos son válidos. Imprime resultados para números pares
  * @param goldbachStruct contiene los resultados
  * @param httpResponse envia la respuesta al usuario.
  */
  void print_even(struct golbachElement goldbachStruct
  , HttpResponse& httpResponse);

  /**
  * @brief Imprimime los resultados de la suma de Goldbach cuando
  * los datos son válidos. Imprime resultados para números impares
  * @param goldbachStruct ontiene los resultados
  * @param httpResponse envia la respuesta al usuario.
  */
  void print_odd(struct golbachElement goldbachStruct
  , HttpResponse& httpResponse);

  /**
  * @brief Llamado general a imprimir los resultados
  * se divide acorde a la conjetura, débil o fuerte
  * @param goldbachStruct Arreglo con todos los resultados obtenidos
  * de los números ingresados.
  * @param httpResponse muestra los resultados al usuario
  */
  void goldbach_print(std::vector<golbachElement> golbachElements
  , HttpResponse& httpResponse);
};
#endif
