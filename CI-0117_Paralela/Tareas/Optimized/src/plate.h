// Copyright [2025] <Camila Rodríguez>

#ifndef TAREAS_PTHREADS_SRC_PLATE_H_
#define TAREAS_PTHREADS_SRC_PLATE_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

/**
 * @file plate.h
 * @brief Declaraciones de estructuras y funciones para la simulación de difusión
 * térmica en una placa.
 */

/**
 * @struct Plate
 * @brief Representa los parámetros físicos necesarios para la simulación de una
 * placa térmica.
 */
typedef struct {
    char archivo_lamina[256];
    double delta_t;
    double alpha;
    double h;
    double epsilon;
} Plate;

/**
 * @brief Crea una estructura Plate a partir de una línea de texto con los parámetros.
 *
 * @param linea Cadena de texto con los parámetros de la placa.
 * @param iteracionesArray Arreglo donde se almacenará el número de iteraciones
 * esperadas.
 * @param contador Contador del número de placas procesadas.
 * @param numThreads Número de hilos a utilizar en la simulación.
 */
void crear_plate(const char *linea,
    int *iteracionesArray, int *contador, const char *jobDir);

/**
 * @brief Lee un archivo binario con datos de temperatura y ejecuta la simulación
 * de la placa.
 *
 * @param nombreBin Nombre del archivo binario a leer.
 * @param plate Puntero a una estructura Plate con los parámetros físicos de la
 * simulación.
 * @param iteracionesArray Arreglo donde se almacenará el número de iteraciones
 * realizadas.
 * @param contador Puntero a una variable que contabiliza las iteraciones totales.
 * @param numThreads Número de hilos a utilizar en la simulación.
 */
void leer_plate(const char *nombreBin, const Plate *plate,
    int *iteracionesArray, int *contador);

/**
 * @brief Ejecuta la simulación de difusión térmica en una placa.
 *
 * @param temperaturas Arreglo con las temperaturas iniciales.
 * @param filas Número de filas de la matriz de temperatura.
 * @param columnas Número de columnas de la matriz de temperatura.
 * @param plate Puntero a una estructura Plate con los parámetros físicos de la
 * simulación.
 * @param numThreads Número de hilos a utilizar en la simulación.
 * @return Número de iteraciones realizadas hasta la convergencia.
 */
int simular_difusion(double *temperaturas, uint64_t filas, uint64_t columnas,
                     const Plate *plate);

/**
 * @brief Copia los valores de los bordes de una matriz de temperatura a otra.
 * 
 * @param temperaturas Puntero a la matriz de temperatura actual.
 * @param nueva_temp Puntero a la nueva matriz donde se copiarán los bordes.
 * @param filas Número de filas en ambas matrices.
 * @param columnas Número de columnas en ambas matrices.
 */
void copiar_boundaries(double *temperaturas, double *nueva_temp, uint64_t filas,
                       uint64_t columnas);

#endif  // TAREAS_PTHREADS_SRC_PLATE_H_
