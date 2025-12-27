// Copyright [2025] <Copyright Owner>

#ifndef TAREAS_PTHREADS_SRC_REPORT_H_
#define TAREAS_PTHREADS_SRC_REPORT_H_

#include <time.h>

/**
 * @brief Crea un reporte con los resultados de la simulación térmica.
 * 
 * @param jobPath Ruta al archivo de trabajo que contiene los datos de entrada.
 * @param iteracionesArray Arreglo con el número de iteraciones por simulación.
 */

void crear_reporte(const char *jobPath, int *iteracionesArray);

/**
 * @brief Formatea una marca de tiempo en una cadena legible.
 * 
 * @param seconds Tiempo en segundos desde la época UNIX.
 * @param text Buffer donde se almacenará la cadena formateada.
 * @param capacity Tamaño del buffer.
 * @return Puntero a la cadena formateada.
 */

char* format_time(const time_t seconds, char* text, const size_t capacity);

#endif  // TAREAS_PTHREADS_SRC_REPORT_H_
