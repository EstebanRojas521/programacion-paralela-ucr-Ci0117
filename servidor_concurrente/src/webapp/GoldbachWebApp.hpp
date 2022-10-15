// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef GOLDBACHWEBAPP_HPP
#define GOLDBACHWEBAPP_HPP

#include <string>
#include <vector>
#include <csignal>

#include "HttpApp.hpp"
#include "HttpPackage.hpp"
//#include "SumGoldbachModel.hpp"
#include "GoldbachResponder.hpp"
#include "common.hpp"

  /**
  * @brief A web application that calculates sums of goldbach
  */
class GoldbachWebApp : public HttpApp{
  /// Objects of this class cannot be copied
  DISABLE_COPY(GoldbachWebApp);

 protected:
  
  GoldbachResponder goldbachResponder;

  /**
   @brief Count of solvers.
    By default the program uses the number of cores in the computer.
  */
  int solvers_count = std::thread::hardware_concurrency();

 public:
  /**
  @brief Constructor of GoldbachWebApp.
  */
  GoldbachWebApp();

  /**
  * @brief Destructor of GoldbachWebApp.
  */
  ~GoldbachWebApp();

  /**
  * @brief Called by the web server when the web server is started.
  */
  void start() override;

  /**
  * @brief Called when the web server stops, in order to allow the web
  * application clean itself and finish as well
  */
  void stop() override;

  /**
  * @brief Handles the request made by an user.
  * @param httpPackage Contains the request and response made by an user
  */

  bool handleHttpRequest(HttpPackage& httpPackage) override;

protected:

  /**
   * @brief Takes a package from the queue.
   * @param httpPackage Contains the request and response made by an user
   */
  
  void consume(HttpPackage httpPackage) ;


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
  void createVectorOfNumbers(int start
  , int finish, const std::string URI
  , std::vector<int64_t>& numbers);

  /**
   * @brief This method converts a string to int64_t if it is a number.
   * @details This method validates if a string of numbers has
   * the right size to be converted to int64_t.
   * @param number The number in string form to convert.
   * @param converted_number The converted number if it can be converted.
   * @return true or false if it succeeds in conversion
  */
  bool convertStringToInt(std::string& number
  , int64_t& converted_number);

  /**
   * @brief Replaces characters with other characters
   * The method replaces all occurrences of a string,
   * with another one that is more functional
   * @param str The row to be replaced with
   * @param from The subrow to replace
   * @param to The subrow to be replaced by
  */
  void replaceCharacters(std::string& str,
  const std::string& from, const std::string& to);
};

#endif  // GOLDBACHWEBAPP_HPP
