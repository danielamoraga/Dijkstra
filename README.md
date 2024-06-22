# Dijkstra

Descripción del proyecto

## Requisitos

- GCC
- Make

## Estructura del proyecto

Descripción de los archivos principales y su función

- `dijkstra.hpp`: Este archivo contiene la implementación del algoritmo de Dijkstra para encontrar el camino más corto en un grafo. Utiliza estructuras de datos definidas en `structures.hpp` para representar el grafo y realizar los cálculos necesarios.
- `main.cpp`: Este es el punto de entrada del programa. Incluye la lógica para generar grafos aleatorios mediante get_random_weight y ejecutar el algoritmo de Dijkstra definido en `dijkstra.hpp`. También contiene una función de depuración `debug` para imprimir los resultados del algoritmo.
- `Makefile`: Contiene las instrucciones para compilar y ejecutar el proyecto. Define comandos como `make run` para ejecutar el experimento y `make clean` para eliminar los archivos generados durante la compilación, facilitando la gestión del ciclo de vida del software.
- `structures.hpp`: Define las estructuras de datos esenciales para el proyecto, como `graph`, `heap`, `bintree`, y `fibheap`. `graph` es particularmente importante, ya que representa el grafo sobre el cual se ejecuta el algoritmo de Dijkstra, incluyendo métodos para agregar aristas y almacenar la lista de adyacencia.

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