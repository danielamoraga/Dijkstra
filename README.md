# Dijkstra

Este proyecto implementa el algoritmo de Dijkstra para encontrar el camino más corto en un grafo, utilizando diferentes estructuras de datos para la optimización del algoritmo. Se incluyen implementaciones con Heap binomial, Heap de Fibonacci, y otras estructuras auxiliares.

## Requisitos

- GCC
- Make

## Estructura del proyecto

Descripción de los archivos principales y su función

- `Makefile`: Contiene las instrucciones para compilar y ejecutar el proyecto. Define comandos como `make run` para ejecutar la experimentación o `make debug` para debuggear el código.
- `main.cpp`: Punto de entrada del programa. Genera grafos aleatorios, ejecuta el algoritmo de Dijkstra y contiene la función `debug` para imprimir los resultados.
- `dijkstra.hpp`: Implementación del algoritmo de Dijkstra. Utiliza estructuras de datos definidas en `structures.hpp`.
- `structures.hpp`: Define las estructuras de datos esenciales como `graph`, `heap`, `bintree`, y `fibheap`.
- `resultados[i][j].txt`: Archivo de salida donde se escriben los resultados de la experimentación con los algoritmos de Dijkstra utilizando las diferentes estructuras de datos para el grafo con $2^i$ vértices y $2^j$ aristas .

## Características Principales

- **Generación de Grafos Aleatorios**: El programa es capaz de generar grafos aleatorios para la evaluación del algoritmo de Dijkstra, como se muestra en [main.cpp](Dijkstra/main.cpp).
- **Comparación de Estructuras de Datos**: Se realiza una comparación entre el uso de Heap binomial y Heap de Fibonacci para determinar cuál ofrece mejor rendimiento en términos de tiempo de ejecución.
- **Debugging y Pruebas**: Se incluye una función de depuración (`debug`) en [main.cpp](Dijkstra/main.cpp) para facilitar la visualización de los resultados del algoritmo de Dijkstra en grafos de prueba.

## Compilación y Ejecución

Para compilar y ejecutar el proyecto, utiliza los siguientes comandos:

### Para ejecutar el experimento:

```sh
make run
```

## Limpieza

Para limpiar los archivos generados durante la compilación, utiliza el siguiente comando:

```sh
make clean
```
