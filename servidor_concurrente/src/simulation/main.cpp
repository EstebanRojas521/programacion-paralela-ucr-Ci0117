/// @copyright 2020 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Jeisson Hidalgo-Céspedes <jeisson.hidalgo@ucr.ac.cr>

#ifdef SIMULATION

#include "ProducerConsumerTest.hpp"

int main(int argc, char* argv[]) {
  //crear servidor web, el codigo es reutilizable = agnostico al dominio que se va a publicar, puede
  //publicar cualquier aplicacion 
  //crear aplicacion web = agnostico al contexto
  //corremos el servidor = tienen start, stop, restart, configurar, 
  return ProducerConsumerTest().start(argc, argv);
}


//http hay que modiciarlo, codigo van con networl

#endif  // SIMULATION
