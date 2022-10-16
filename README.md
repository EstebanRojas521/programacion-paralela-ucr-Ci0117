# stack_overfloismo

## Integrantes:

- Esteban Rojas Carranza C06816
- Ulises Fonseca Hurtado C03046
- Yasmyn Chacón Hernández B41761

# Descripción del problema

Este programa pretende realizar el cálculo de las sumas de la conjetura de Goldbach, a partir de la modificación de un servidor, para que este se transforme de uno serial a uno concurrente.

# Manual de uso

## **Compilar el código**

Para compilar este código se debe de utilizar el comando: 

`make`

Este genera una carpeta **bin**

## **Ejecutar el programa**
Para ejecutar el programa utilizar el comando:

`bin/servidor_concurrente`

*Nota: si desea acceder a un puerto en especifíco, indicarlo en la misma línea (`bin/servidor_concurrente` 1234) 

Una vez ejecutado el comando, se habilita el puerto indicado o en su defecto el puerto 8080.

Para acceder al servidor web, dirigirse a un navegador e ingresar en la barra de búsqueda la siguiente instrucción: 

`localhost:8080` o el número de puerto seleccionado previamente.

Cuando la página carga se muestras la siguiente interfaz: 

![DiagramaCompleto](/servidor_concurrente/design/image/paginaPrincipal.jpeg)

En la cual la persona usuaria, podrá agregar una lista de números, separados por coma(,) para que sea procesados.

Un vez ingresados los números y dado en el botón "Calcular" se verificarán los datos recibidos y en caso de que ingrese valores que no corresponden a números, se le mostrará un mensaje de error, mientras que si son números, se mostrará el resultado. 

### **Ejemplo:**

![DiagramaCompleto](/servidor_concurrente/design/image/ejemploAplicacion.jpeg)

Como se muestra en la imagen, por cada número ingresado, se muestra la cantidad de sumas que corresponden a cada uno de ellos. 

Cabe destacar, que la persona usuarioa siempre tiene la opción de regresar a la página principal, seleccionando `Back`

Finalmente, se menciona, que se puede interrumpir de forma abrupta el servidor mediante el comando `Kill` o mediante la interrupción `CRTL+C `