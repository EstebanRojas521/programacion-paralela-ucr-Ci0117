/// @copyright 2020 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Jeisson Hidalgo-Céspedes <jeisson.hidalgo@ucr.ac.cr>

#ifndef GOLDBACHSTRUCT_HPP
#define GOLDBACHSTRUCT_HPP

#include <cstdint>

/**
 * @brief The message to be transmitted by the simulated network
 */
struct GoldbachStruct {
 public:
  //cambiar tipo de dato probablemente tire error
  
  /// The target consumer
  int64_t number = 0;
  /// The source producer
  std::vector<int64_t> resultsVector = {0};
  bool first =  false;
  bool last =  false;
  /// The contents of the message (body or payload)

 public:
  /// Convenience constructor
  GoldbachStruct(int64_t number  = 0, std::vector<int64_t>resultsVector = {0}
  ,bool first = false, bool last = false)
    : number(number)
    , resultsVector(resultsVector)
    , first(first)
    ,last(last) {
  }

  // no se necesita creo?
  // Returns true if this message is equals to the given
  inline bool operator==(const GoldbachStruct& other) const {
    return this->number == other.number
      && this->resultsVector == other.resultsVector;
  }
};

#endif  // NETWORKMESSAGE_HPP