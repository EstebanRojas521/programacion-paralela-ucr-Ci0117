
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
  * @brief Checks if the data entered by the user is valid
  * @details If the data are valid, it returns the goldbach sums.
  * @param httpPackage response and request carrier
  */
  void validRequest(HttpPackage httpPackage);


  std::vector<golbachElement> golbachElements;

  void fillUpVector(struct golbachElement& goldbachStruct);
  void cleanUpVector(struct golbachElement& goldbachStruct);
  /**
  * @brief Checks if the data entered by the user is invalid
  * @details If the data is invalid, returns an error response
  * @param httpPackage response and request carrier
  */
  void invalidRequest(HttpPackage httpPackage);

  /**
  * @brief Prints the sums of Goldbach for the even numbers
  * @param goldbachStruct Struct with the results.
  * @param httpResponse Responde made to a user.
  */
  void print_even(struct golbachElement goldbachStruct
  , HttpResponse& httpResponse);

  /**
  * @brief Prints the sums of Goldbach for the odd numbers
  * @param goldbachStruct Struct with the results.
  * @param httpResponse Responde made to a user.
  */
  void print_odd(struct golbachElement goldbachStruct
  , HttpResponse& httpResponse);

  /**
  * @brief Prints all the sums of Goldbach for all the given numbers entered by user
  * @param goldbachStruct Array of all the results of every number entered by the user.
  * @param httpResponse Responde made to a user.
  */
  void goldbach_print(std::vector<golbachElement> golbachElements
  , HttpResponse& httpResponse);
};
#endif
