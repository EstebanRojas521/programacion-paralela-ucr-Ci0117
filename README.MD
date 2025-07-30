Este repositorio agrupa trabajos realizados para el curso **CI‑0117 – Programación Paralela y Concurrente** en la **Universidad de Costa Rica**. En el se encuentran implementaciones que exploran técnicas de paralelismo con OpenMP, programación distribuida con MPI y el diseño de un servidor concurrente en C++. Estos proyectos se enfocan en problemas numéricos reales y en la modificación de software serial para convertirlo en sistemas concurrentes y paralelos.

Integrantes:

- Yasmyn Chacón Hernández B41761
- Ulises Fonseca Hurtado C03046
- Esteban Rojas Carranza C06816

### Estructura del repositorio

- **Proyecto2.1:** Implementa la lectura de datos, conversión de archivos binarios y simulación de transferencia de calor usando la directiva  *pragma omp parallel* para ejecutar múltiples celdas en paralelo. Este programa gestiona un vector de láminas y calcula la difusión de calor sobre cada una de ellas mediante un algoritmo de barrido controlado por hilos. *(Tecnologías: C++ / OpenMP)*

- **Proyecto2.2:** Extiende la simulación de transferencia de calor utilizando MPI para distribuir la carga entre varios procesos. El usuario provee un archivo .txt que define varios trabajos (con nombre de placa, tamaño, tiempo de transferencia, coeficiente de difusión, área y ε). Cada proceso lee matrices desde archivos binarios, actualiza las celdas según la fórmula de difusión y genera reportes en texto y binario. *(Tecnologías: C++, OpenMP, MPI)*

- **servidor_concurrente:** Adapta un servidor web serial para que procese múltiples solicitudes concurrentemente. La aplicación expone una página web donde la persona usuaria introduce una lista de números; el servidor calcula, para cada número, la cantidad de descomposiciones en sumas de dos primos (Conjetura de Goldbach). Incluye interfaz web y documentación de uso. *(Tecnologías: C++, concurrency)*

