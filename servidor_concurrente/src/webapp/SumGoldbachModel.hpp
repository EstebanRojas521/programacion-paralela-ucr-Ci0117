// Copyright 2022  Yasmyn Chacón Hernández,Ulises Fonseca Hurtado
// y Esteban Rojas Carranza - Universidad de Costa Rica.

#ifndef SUMGOLDBACHMODEL
#define SUMGOLDBACHMODEL
#include <vector>
#include <cstdlib>
#include "HttpPackage.hpp"
#include "HttpApp.hpp"
#include "HttpPackage.hpp"
#include "GoldbachHTML.hpp"
#include "common.hpp"
#include <string>


struct NumberStruct{
  int64_t number;
  std::vector<int64_t> smallerPrimes;
  std::vector<int64_t> results;
  int64_t totalPrimes;
};

class SumGoldbachModel{

  public:
    SumGoldbachModel();
    ~SumGoldbachModel();
    int64_t is_prime(int64_t);
    void calculate_smaller_primes(NumberStruct*);
    int64_t check_repeated_even( std::vector<int64_t>, int64_t, int64_t);
    void processEvenSums(NumberStruct*);
    int64_t check_repeated_uneven( std::vector<int64_t>, int64_t,
    int64_t, int64_t);
    void processUnevenSums(NumberStruct*);
    void processGoldbachNumber(NumberStruct*);
    void serveGolbach(int, int, HttpPackage&,std::string);

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
   * @brief  Vector que recibe los números en int
   * @details Asume que se leyó los datos de entrada, y por cada números
   * procesado se guarda en el vector, ocurre hasta que no haya
   * más números por procesar
   * @param URI entrada de datos, que se deben convertir
   * @param numbers números almacenados, para procesar posteriormete
   * @param start inicio de la hilera
   * @param finish fin de la hilera
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
