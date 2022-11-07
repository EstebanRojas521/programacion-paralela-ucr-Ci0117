// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#ifndef SUMGOLDBACHMODEL
#define SUMGOLDBACHMODEL
#include <cstdlib>
#include <string>
#include <vector>
#include "common.hpp"
#include "GoldbachHTML.hpp"
#include "HttpApp.hpp"
#include "HttpPackage.hpp"


struct NumberStruct{
  // Numero ingresado por usuario
  int64_t number;
  // Arreglo de numeros primos
  std::vector<int64_t> smallerPrimes;
  // Arreglo con los numeros respectivos a las sumas de goldbach
  std::vector<int64_t> results;
};

class SumGoldbachModel{
 public:
  /**
   * @brief Constructor de SumGoldbachModel
   */
  SumGoldbachModel();

  /**
   * @brief Destructor de SumGoldbachModel
   * 
   */
  ~SumGoldbachModel();

  /**
   * @brief Metodo que verifica si un numero es primo o no
   * @param number Numero a verificar
   * @return int64_t Retorna 0 si el numero es primo, sino retorna 1
   */
  int64_t isPrime(int64_t number);

  /**
   * @brief Metodo que calcula los numeros primos menores que x numero
   * @details Se guardan los numeros primos dentro de vector del struct
   * @param numberStruct Struct de donde se saca numero a calcular sus primos
   */
  void calculateSmallerPrimes(NumberStruct* numberStruct);

  /**
   * @brief Metodo que revisa si una serie de numeros ya fue ingresada en diferente orden en un vector 
   * @param sumsVector Vector donde se revisa
   * @param num1 Primer numero a revisar
   * @param num2 Segundo numero a revisar
   * @return int64_t Retorna 1 si la serie existe, retorna 0 si no
   */
  int64_t checkRepeatedEven(std::vector<int64_t> sumsVector,
                                 int64_t num1, int64_t num2);

  /**
   * @brief Metodo que calcula y añade a vector series de numeros
   * @details Los numeros agregados corresponden a las propias sumas de goldbach
   *          del numero correspondiente al NumberStruct, en este caso es especificamente
   *          un numero par. Si se recibe un 1 del llamado a checkRepeatedEven
   *          con los numeros a agregar, valga la redundancia no se agregan al arreglo
   *          de sumas de goldbach, pues ya la serie existe, solo que en otro orden.
   * @param numberStruct Recibe struct de donde saca el numero, y los numeros primos
   *                      menores que si para calcular sus sumas de goldbach
   * @return int64_t Retorna un int64_t, 0 en caso de exito al añadir memoria,
   *         1 en caso contrario 
   */
  void processEvenSums(NumberStruct* numberStruct);

  /**
   * @brief @see checkRepeatedEven
   * @details El metodo recibe en este caso 3 numeros a revisar pues se trata de 
   *          calcular las sumas de goldbach de un numero impar
   * @param sumsVector @see checkRepeatedEven
   * @param num1 Primer numero a revisar
   * @param num2 Segundo numero a revisar
   * @param num3 Tercer numero a revisar
   * @return int64_t 
   */
  int64_t checkRepeatedUneven(std::vector<int64_t> sumsVector, int64_t num1,
  int64_t num2, int64_t num3);

  /**
   * @brief @see processEvenSums
   * @details En este caso, el numero contenido en numberStruct es impar y dentro se
   *          llama a check_repeated_uneven
   * @param numberStruct @see processEvenSums
   * @return int64_t @see processEvenSums
   */
  void processUnevenSums(NumberStruct* numberStruct);

  /**
   * @brief Metodo que procesa las sumas de goldbach generales
   * @details Si el numero es par lo manda a processEvenSums, sino lo manda a processUnevenSums
   * @param numberStruct Struct de donde se saca el numero ingresado por el usuario
   */
  void processGoldbachNumber(NumberStruct* numberStruct);

  /**
   * @brief Metodo que procesa los numeros ingresados por el usuario con base en el URI
   * @details Recibe un package donde guarda en un vector dentro de el los numeros ingresados
   *          por el usuario con base en el URI, posteriormente procesa los numeros y renderiza
   *          la informacion en formato HTML
   * @param start Posicion donde se empieza a leer el URI donde esta el primer numero ingresado
   * @param finish Posicion final del URI
   * @param httpPackage Paquete recibido
   * @param URI URI recibida
   */
  void serveGolbach(int start, int finish, HttpPackage& httpPackage,
                                            std::string URI);

  /** 
   * @brief  Method that stores in64_t numbers present in a row, in a vector.
   * vector.
   * @details This method assumes that the row has passed through the regex of the method
   * extractNumbersFromURI method, so it iterates over the row until it * encounters a + character.
   * encounters a + character. If it finds it, then it tries to perform the
   * conversion to number, if the conversion is unsuccessful it stops iterating and stops
   * convert the numbers.
   * @param URI string of characters to be parsed.
   * @param numbers The vector where the numbers will be stored after reading them.
   * @param start beginning of the string
   * @param finish Where the string ends
   */
  void createVectorOfNumbers(int start , int finish, const std::string URI,
                                                std::vector<int64_t>& numbers);

  /** 
   * @brief Metodo que convierte una hilera a numero
   * @param number hilera a convertir en numero
   * @param converted_number numero convertido desde la hilera number
   * @return retorna false si convirtio el numero con exito, true caso contrarioS
   */
  bool convertStringToInt(std::string& number, int64_t& converted_number);


  /**
   * @brief Imprimime los resultados de la suma de Goldbach cuando
   * los datos son válidos. Imprime resultados para números pares
   * @param goldbachStruct contiene lnumberos resultados
   * @param httpResponse envia la respuesta al usuario.
   */
  void print_even(struct NumberStruct* goldbachStruct,
                                              HttpResponse& httpResponse);

  /**
   * @brief Imprimime los resultados de la suma de Goldbach cuando
   * los datos son válidos. Imprime resultados para números impares
   * @param goldbachStruct ontiene los resultados
   * @param httpResponse envia la respuesta al usuario.
   */
  void print_odd(struct NumberStruct* goldbachStruct,
                                              HttpResponse& httpResponse);

  /**
   * @brief Llamado general a imprimir los resultados
   * se divide acorde a la conjetura, débil o fuerte
   * @param goldbachStruct Arreglo con todos los resultados obtenidos
   * de los números ingresados.
   * @param httpResponse muestra los resultados al usuario
   */
  void goldbach_print(struct NumberStruct* goldbachStruct,
                                              HttpResponse& httpResponse);
};

#endif
