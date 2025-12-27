// Copyright [2025] <Camila Rodríguez>

#ifndef TAREAS_SERIAL_SRC_PLATE_H_
#define TAREAS_SERIAL_SRC_PLATE_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <linux/time.h>

typedef struct {
    char archivo_lamina[256];
    double delta_t;
    double alpha;
    double h;
    double epsilon;
} Plate;


/**
 * @brief Procesa una línea del archivo de entrada y carga los datos en una estructura Plate.
 *
 * @param linea Línea del archivo de entrada con los datos de la placa.
 * @param iteracionesArray Arreglo donde se almacenará el número de iteraciones para después generar el reporte.
 * @param contador Contador de archivos.
 */

void crear_plate(const char *linea, int *iteracionesArray, int *contador);


/**
 * @brief Lee un archivo binario que contiene información sobre la placa y simula su difusión térmica.
 *
 * @param nombreBin Nombre del archivo binario.
 * @param plate Puntero a la estructura Plate con los parámetros.
 * @param iteracionesArray Arreglo donde se almacenará el número de iteraciones.
 * @param contador Contador de iteraciones.
 */

void leer_plate(const char *nombreBin, const Plate *plate,
    int *iteracionesArray, int *contador);

/**
 * @brief Simula la difusión térmica en la placa hasta que los cambios sean menores que epsilon.
 *
 * @param temperaturas Matriz de temperaturas.
 * @param filas Número de filas de la matriz.
 * @param columnas Número de columnas de la matriz.
 * @param plate Puntero a la estructura Plate con los parámetros.
 * @return Número de iteraciones realizadas.
 */

int simular_difusion(double *temperaturas, uint64_t filas, uint64_t columnas,
                     const Plate *plate);

#endif  // TAREAS_SERIAL_SRC_PLATE_H_
