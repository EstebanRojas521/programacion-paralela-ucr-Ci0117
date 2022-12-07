### Proyecto 2.2 Análisis de rendimiento

En esta etapa del proyecto en primera instancia se creó toda la lectura de archivos, simulación de calor y escritura de forma serial.

Luego, para definir cuál parte del código era mejor de implementar concurrentemente, se utilizó la herramienta kcachegrind. Esta herramienta se utilizó para determinar cuáles eran subrutinas del código son las que tomaban más tiempo en finalizar, para así hacerlas paralelas.

Los resultados fueron los siguientes:

![image info](./desing/imagesReport/ReportKcachegrind%231.png)

![image info](./desing/imagesReport/ReportKcachegrind%232.png)

Como se logra observar, las subrutinas las cuales consumen más tiempo corresponden a la simulación de calor. Por lo tanto, esas subrutinas se harán de forma concurrente.

Asi mismo en esta segunda etapa del proyecto no unicamente se paralelizo esa zona critica, sino que se busco crear diferentes procesos los cuales ejecuten el codigo de forma concurrente utilizando MPI. Esto signfica que si una archivo de texto con seis lineas se corre con dos procesos, cada proceso se encargaria de procesar tres lineas del archivo de texto.

Posterior a realizar la implementacion de la concurrencia, se obtuvo la siguiente grafica:
![image info](./desing/imagesReport/graficaSpeedupEfficiency.png)
