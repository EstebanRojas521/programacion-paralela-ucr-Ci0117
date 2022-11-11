// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef GOLDBACHWEBAPP_HPP
#define GOLDBACHWEBAPP_HPP

#include <csignal>
#include <string>
#include <thread>
#include <vector>

#include "HttpApp.hpp"
#include "HttpPackage.hpp"
#include "SumGoldbachModel.hpp"
#include "common.hpp"
#include "AppAssembler.hpp"
/**
* @brief A web application that calculates sums of goldbach
*/
class GoldbachWebApp : public HttpApp{
  /// Objects of this class cannot be copied
  DISABLE_COPY(GoldbachWebApp);

 protected:
  /**
   * @brief Count of solvers.
   * By default the program uses the number of cores in the computer.
   */
  int solvers_count = std::thread::hardware_concurrency();

 public:
  /**
   * @brief Constructor de GoldbachWebApp.
   */
  GoldbachWebApp();


    int run() override;

  /**
   * @brief Metodo que consume HttpPackages
   * @param package El package a consumir
   */
    void consume(HttpPackage package) override;

  /**
   * @brief Destructor de GoldbachWebApp.
   */
  ~GoldbachWebApp();

  /** 
   * @brief Metodo que convierte una hilera a numero
   * @param number hilera a convertir en numero
   * @param converted_number numero convertido desde la hilera number
   * @return retorna false si convirtio el numero con exito, true caso contrarioS
   */
  bool convertStringToInt(std::string& number, int64_t& converted_number);



  /** 
   * @brief Se llama cuando el servidor se inicia
   */
  void start() override;

  /**
   * @brief Se llama cuando el servidor es detenido, para que
   * detenga, cada una de las aplicaciones en usp
   */
  void stop() override;

  /**
   * @brief Empaquetado de respuestas y solicitudes
   * @param httpPackage Paquete a validar
   * @return true 
   * @return false 
   */
  bool handleHttpRequest(HttpPackage& httpPackage) override;


  // bool appFound(HttpPackage& httpPackage) override;
 protected:
  /**
   * @brief Consume las solicitudes disponibles en la cola
   * @param httpPackage contiene las solicitudes y respuestas
   */
  // void consume(HttpPackage httpPackage);

  bool serveHomePage(HttpPackage httpPackage);

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
  void createVectorOfNumbers(int start, int finish, const std::string URI
                                          , std::vector<int64_t>& numbers);

  /**
   * @brief reemplaza los caracteres por unos más funcionales
   * es decir, cambia la , (%2C) por un +, para facilitar la manipulación
   * @param str lugar que se debe de reemplazar
   * @param from Caracter a reemplazar
   * @param to Caracter de reemplazo
   */
  void replaceCharacters(std::string& str, const std::string& from,
                                            const std::string& to);

  /**
   * @brief Si los datos no son válidos, se ingresa a este método
   * @details se retorna un mensaje de error cuando los datos dados
   * son inválidos
   * @param httpPackage paquete de solicitudes y respuestas
   */
  void invalidRequest(HttpPackage httpPackage);
};

#endif  // GOLDBACHWEBAPP_HPP
