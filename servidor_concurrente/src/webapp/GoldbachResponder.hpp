
#ifndef GOLDBACHRESPONDER_H
#define GOLDBACHRESPONDER_H

#include <string>
#include <vector>

#include "common.hpp"
#include "Consumer.hpp"
#include "HttpPackage.hpp"

 /**
  * @brief Creates the response that it's send to the user.
  */
 
class GoldbachResponder{
  DISABLE_COPY(GoldbachResponder);

 public:
  /**
  * @brief Default constructor.
  */
  GoldbachResponder();
  ~GoldbachResponder();

  /**
  * @brief Checks if the data entered by the user is valid
  * @details If the data are valid, it returns the goldbach sums.
  * @param httpPackage response and request carrier
  */
  void validRequest(HttpPackage httpPackage);

  /**
  * @brief Checks if the data entered by the user is invalid
  * @details If the data is invalid, returns an error response
  * @param httpPackage response and request carrier
  */
  void invalidRequest(HttpPackage httpPackage);

  /**
  * @brief Prints the sums of Goldbach for the even numbers
  * @param results Struct with the results.
  * @param httpResponse Responde made to a user.
  */
  void print_even_number(struct result results
  , HttpResponse& httpResponse);

  /**
  * @brief Prints the sums of Goldbach for the odd numbers
  * @param results Struct with the results.
  * @param httpResponse Responde made to a user.
  */
  void print_odd_number(struct result results
  , HttpResponse& httpResponse);

  /**
  * @brief Prints all the sums of Goldbach for all the given numbers entered by user
  * @param results Array of all the results of every number entered by the user.
  * @param httpResponse Responde made to a user.
  */
  void goldbach_print(std::vector<result> results
  , HttpResponse& httpResponse);
};
#endif
