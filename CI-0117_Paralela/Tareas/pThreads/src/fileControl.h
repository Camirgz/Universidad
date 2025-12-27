// Copyright [2025] <Camila Rodríguez>

#ifndef TAREAS_PTHREADS_SRC_FILECONTROL_H_
#define TAREAS_PTHREADS_SRC_FILECONTROL_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
  * @brief Escribe los resultados de una simulación térmica en un archivo binario nuevo (resultado).
 *
 * Crea el directorio "resultados" si no existe y genera un archivo con un nombre
 * basado en el nombre original y el número de iteraciones.
 *
 * @param nombreBin Nombre del archivo binario original.
 * @param temperaturas Puntero a los datos de temperatura a escribir.
 * @param filas Número de filas de la matriz de temperaturas.
 * @param columnas Número de columnas de la matriz de temperaturas.
 * @param iteraciones Número de iteraciones de la simulación.
 */

void escribir_resultado(const char *nombreBin, double *temperaturas,
                        uint64_t filas, uint64_t columnas, int iteraciones);


/**
 * @brief Elimina todos los archivos dentro de un directorio dado.
 *
 * Si el directorio no existe, lo crea.
 *
 * @param[in] directorio Ruta del directorio a limpiar.
 */

void limpiar_directorio(const char *directorio);

#endif  // TAREAS_PTHREADS_SRC_FILECONTROL_H_
