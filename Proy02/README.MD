### Problema a resolver 


El presente codigo busca simular la transferencia de calor entre materiales. La manera realizar esta simulacion es atravez de una matriz, la cual cada celda representa una celda dentro del material el cual va a transferir o perder calor. La transferencia funciona de celda a la misma celda, por ejemplo se calcula la perdida o ganacia de la celda 2,2, y su resultado se almacena nuevamente en la celda 2,2. Los datos que utilizan dentro de esta transferencia corresponde a cuanto dura cada tranferencia (pueden existir multiples), el grado de difusion del material , el area de cada celda del material y el epsilon. Estos datos son importantes ya que para calcular la perdida o ganancia de calor de cada celda se debe dictar atraves de una formula la cual incluye todas estas variables.

A continuacion un ejemplo de una transferencia de calor:

![image info](./desing/imagesReport/heatTransferExample.png)

Imagen 1.1 obtenida de http://jeisson.work/concurrente/2021b/proyectos/heat/

Tomemos por ejemplo la celda (1,2) la cual tiene un valor de 0 y luego 2.734. Este nuevo valor fue calculado utilizando la formula tiempo*difusion sobre area + la suma de calor de las celdas a su derecha,izquierda,arriba y abajo - 4 por el calor de la celda sobre el area mas el calor actual. Por lo tanto, este codigo busca resolver todas estas transfencias de calor hasta que el punto de equilibrio haya sido alcanzado. Asi mismo se busca leer las placas desde un archivo binario y escribir sus resultado de igual forma en un archivo binario, asi como crear un archivo de texto con los resultado de la simulacion.

### Manual de usuario

El codigo para compilar requiere un archivo de texto el cual contenga los datos necesarios para la simulacion y el nombre de un archivo binario el cual contenga la matriz inicial. En este codigo todos esos datos se encuentran en la carpeta jobs/ y los resultados y reportes de la compilacion seran almacenados en la carpeta output/ . Este codigo unicamente recibe archivos .txt(job001.txt por ejemplo) como primer parametro y la cantidad de hilos que se usararan durante la simulacion como segundo parametro.

Un ejemplo para correr el presente codigo corresponde a:


![image info](./desing/imagesReport/runCodeExample%231.png)

donde job0001.txt corresponde al .txt que se encuentra de la carpeta jobs/ que se utilizara durante la simulacion y 10 corresponde al numero de hilos.

Los resultados seran escritos en la carpeta output/

Este codigo cuenta con un programa de pruebas para verificar si los resultados obtenidos fueron los deseados, donde el programa de pruebas cuenta con su propio manual de usuario dentro de su carpeta.

Resumen:
1. Hacer make
2. Escribir ./bin/Proy02 job###.txt #DeHilos
3. Observar resultados .tsv en la carpeta output 
4. Verificar con el programa de pruebas los resultados binarios

### Construccion

En primer lugar se comenzo leyendo el archivo.txt el cual contenia los datos requeridos para comenzar con la simulacion, utilizando las libreria fstream. Donde todos estos datos se almacenaron en un struct.

Luego se procedio a leer el archivo binario el cual contiene cada matriz inicial y se almacenaron los datos para la simulacion en un struct de lamina_t (ver lamina.hpp)

Siguiente, se creo una simulacion la cual recibiera ese struct de lamina_t como parametro y almacenara la matriz resultante en ese mismo struct.

Por ultimo, se creo una clase la cual se encargara de crear el reporte utilizando el struct el cual contiene los datoss obtenidos.
