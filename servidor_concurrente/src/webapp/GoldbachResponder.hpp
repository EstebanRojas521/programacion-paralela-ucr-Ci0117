// // Copyright 2022 CC BY 4.0

// #ifndef GOLDBACHRESPONDER_H
// #define GOLDBACHRESPONDER_H

// #include <string>
// #include <vector>

// #include "common.hpp"
// #include "Consumer.hpp"
// #include "HttpPackage.hpp"

//  /**
//   * @brief Solicitudes enviadas por la persona usuaria
//   */
 
// class GoldbachResponder: public Consumer<HttpPackage> {
//   DISABLE_COPY(GoldbachResponder);

//  public:
//   /**
//   * @brief constructor.
//   */
//   GoldbachResponder();

//   /**
//   * @brief Consume solicitudes constantemente de la cola.
//   */
//   int run() override;

//   /**
//   * @brief consume y verifica si es válido
//   */
//   void consume(HttpPackage httpPackage) override;

//   /**
//   * @brief Verifica si los datos son válidos
//   * @details Si son validos, procesa los datos
//   * @param httpPackage solicitudes y respuestas
//   */
//   void solicitudValida(HttpPackage httpPackage);

//   /**
//   * @brief Si no es válido, se pasa a este método
//   * @details Se responde con un msj de error
//   * @param httpPackage solicitudes y respuestas
//   */
//   void solicitudInvalida(HttpPackage httpPackage);

//   //  Agregar impresión de respuestas de Goldbach

// };
// #endif
