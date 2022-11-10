/// @copyright 2020 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Jeisson Hidalgo-Céspedes <jeisson.hidalgo@ucr.ac.cr>

#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include <cassert>

//#include "Consumer.hpp"
//#include "Producer.hpp"
#include "Queue.hpp"
#include "Thread.hpp"
/**
 * @brief An assembler is a worker of a assembly line. It receives incomplete
 * products, does some pre-defined work of them, and the resulting product
 * continues the assembly line, where other workers will add more parts. See
 * https://en.wikipedia.org/wiki/Assembly_line for the term assembler.
 * 
 * An assembler is both, a consumer of incomplete products coming from a
 * consuming queue, and a producer that pushes results to a queue. The data type
 * of coming products may be different of the products that the Assembler
 * produces.
 * 
 * This class is abstract. You should inherit a class from Assembler and
 * override the consume() method, that is called each time a product is
 * consumed, then do some work with the product, and finally call produce()
 * to push the resulting product to the assembly line.
 */
template <typename DataType>
class Assembler: public virtual Thread{
  /// Objects of this class cannot be copied
  DISABLE_COPY(Assembler);
protected:
    Queue<DataType>* consumingQueue;
    Queue<DataType>* producingQueue;
    const DataType stopCondition;
    bool ownsQueue;
 public:
  /// Constructor
  explicit Assembler(Queue<DataType>* consumingQueue = nullptr
    , Queue<DataType>* producingQueue = nullptr,
    const DataType& stopCondition = DataType(),
    bool createOwnQueue = false)
    : consumingQueue(consumingQueue)
    //aqui va coma o dos puntos
    , producingQueue(producingQueue)
    , stopCondition(stopCondition)
    , ownsQueue(createOwnQueue) {
    // Error if asked to create own queue and provided an existing one to use
    assert(!(createOwnQueue && consumingQueue));
    if (createOwnQueue) {
      this->createOwnQueueASBM();
    }
  }



  /// Destructor
  virtual ~Assembler() {
     if (this->ownsQueue) {
      delete this->consumingQueue;
    }
  }


  /// Get access to the queue where this thread will consume
  inline Queue<DataType>* getConsumingQueueASBM() {
    return this->consumingQueue;
  }

  /// Set the queue where this thread will consume elements
  inline void setConsumingQueueASBM(Queue<DataType>* consumingQueue) {
    this->consumingQueue = consumingQueue;
  }

  /// Creates a new empty queue owned by this consumer
  void createOwnQueueASBM() {
    assert(this->consumingQueue == nullptr);
    this->consumingQueue = new Queue<DataType>();
    this->ownsQueue = true;
  }

  /// Consumes from its queue, util the stop condition is popped
  /// For each data consumed, the @a consume method will be called
  virtual void consumeForeverASBM() {
    assert(this->consumingQueue);
    while (true) {
      // Get the next data to consume, or block while queue is empty
      const DataType& data = this->consumingQueue->pop();
      // If data is the stop condition, stop the loop
      if ( data == this->stopCondition ) {
        break;
      }
      // Process this data
      this->consumeASBM(data);
    } 
  }

    inline Queue<DataType>* getProducingQueueASBM() {
    return this->producingQueue;
  }

  inline void setProducingQueueASBM(Queue<DataType>* producingQueue) {
    this->producingQueue = producingQueue;
  }

  virtual void produceASBM(const DataType& data) {
    assert(this->producingQueue);
    this->producingQueue->push(data);
  }



  /// Override this method to process any data extracted from the queue
  virtual void consumeASBM(DataType data) = 0;

};

#endif  // ASSEMBLER_HPP
