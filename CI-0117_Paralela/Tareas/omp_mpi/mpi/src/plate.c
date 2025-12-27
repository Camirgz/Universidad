// Copyright [2025] <Camila Rodríguez>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>
#include <mpi.h>
#include "plate.h"  //NOLINT
#include "fileControl.h"

// Función para copiar las condiciones de frontera
void copiar_boundaries(double *temperaturas, double *nueva_temp,
    uint64_t filas, uint64_t columnas) {
    // Copiar filas de arriba y abajo para los límites
    for (size_t j = 0; j < columnas; j++) {
        nueva_temp[0 * columnas + j] = temperaturas[0 * columnas + j];
        nueva_temp[(filas - 1) * columnas + j] =
        temperaturas[(filas - 1) * columnas + j];
    }

    // Copiar columnas de izquierda y derecha para los límites
    for (size_t i = 1; i < filas - 1; i++) {
        nueva_temp[i * columnas + 0] = temperaturas[i * columnas + 0];
        nueva_temp[i * columnas + (columnas - 1)]
        = temperaturas[i * columnas + (columnas - 1)];
    }
}

// Función que simula la difusión térmica
int simular_difusion_mpi(double *temperaturas, uint64_t filas,
                        uint64_t columnas, const Plate *plate) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Calcular división de filas por proceso
    uint64_t filas_internas = filas - 2;  // Filas sin bordes
    uint64_t filas_por_proceso = filas_internas / size;
    uint64_t filas_extra = filas_internas % size;

    // Calcular el rango de filas para este proceso
    uint64_t fila_inicio = 1 + (uint64_t)rank * filas_por_proceso +
    ((uint64_t)rank < filas_extra ? (uint64_t)rank : filas_extra);
    uint64_t num_filas_proceso = filas_por_proceso +
    (rank < filas_extra ? 1 : 0);
    uint64_t fila_fin = fila_inicio + num_filas_proceso;

    // Buffer para almacenar la nueva temperatura
    double *buffer = (double *)malloc(filas * columnas * sizeof(double));
    if (!buffer) {
        printf("Error: No se pudo asignar memoria para el buffer en proceso %d.\n", rank); //NOLINT
        return 0;
    }

    double *src = temperaturas;
    double *dst = buffer;
    int iteraciones = 0;
    double coef = plate->alpha * plate->delta_t / (plate->h * plate->h);
    double cambioMax, cambioMaxGlobal;

    do {
        // Copiar boundaries (solo proceso 0 necesita hacer esto)
        if (rank == 0) {
            copiar_boundaries(src, dst, filas, columnas);
        }

        // Broadcast de la matriz actualizada a todos los procesos
        MPI_Bcast(dst, filas * columnas, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        cambioMax = 0.0;

        // Cada proceso calcula su porción de filas
        for (uint64_t i = fila_inicio; i < fila_fin; i++) {
            for (uint64_t j = 1; j < columnas - 1; j++) {
                uint64_t idx = i * columnas + j;
                double arriba   = src[(i - 1) * columnas + j];
                double abajo    = src[(i + 1) * columnas + j];
                double izquierda = src[i * columnas + (j - 1)];
                double derecha   = src[i * columnas + (j + 1)];

                double nuevoValor = src[idx] +
                   coef * (arriba + abajo +
                    izquierda + derecha - 4.0 * src[idx]);
                dst[idx] = nuevoValor;

                double cambio = fabs(nuevoValor - src[idx]);
                if (cambio > cambioMax)
                    cambioMax = cambio;
            }
        }

        // Reducir el cambio máximo entre todos los procesos
        MPI_Allreduce(&cambioMax, &cambioMaxGlobal, 1,
            MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);

        iteraciones++;

        // Intercambiar punteros
        double *temp = src;
        src = dst;
        dst = temp;
    } while (cambioMaxGlobal > plate->epsilon);

    // Recolectar resultados finales en el proceso 0
    if (rank == 0) {
        // El proceso 0 ya tiene su parte
        for (int p = 1; p < size; p++) {
            uint64_t fila_inicio_p = 1 + p * filas_por_proceso + (p < filas_extra ? p : filas_extra); //NOLINT
            uint64_t num_filas_p = filas_por_proceso +
            (p < filas_extra ? 1 : 0);

            for (uint64_t i = fila_inicio_p; i < fila_inicio_p + num_filas_p; i++) { //NOLINT
                MPI_Recv(&src[i * columnas], columnas, MPI_DOUBLE, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); //NOLINT
            }
        }
    } else {
        // Otros procesos envían sus resultados al proceso 0
        for (uint64_t i = fila_inicio; i < fila_fin; i++) {
            MPI_Send(&src[i * columnas], columnas, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD); //NOLINT
        }
    }

    // Copiar resultado final a la matriz original (solo proceso 0)
    if (rank == 0) {
        if (src != temperaturas) {
            memcpy(temperaturas, src, filas * columnas * sizeof(double));
        }
    }

    free(buffer);

    if (rank == 0) {
        printf("Difusión con MPI completada en %d iteraciones.\n", iteraciones);
    }

    return iteraciones;
}

// Función para leer el plate desde un archivo binario
int leer_plate_mpi(const char *nombreBin, const Plate *plate) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    uint64_t filas, columnas;
    double *temperaturas = NULL;
    int iteraciones = 0;

    // Solo el proceso 0 lee el archivo
    if (rank == 0) {
        FILE *bin = fopen(nombreBin, "rb");
        if (!bin) {
            perror("Error al abrir el archivo binario");
            // Enviar señal de error a otros procesos
            filas = 0;
            columnas = 0;
            MPI_Bcast(&filas, 1, MPI_UINT64_T, 0, MPI_COMM_WORLD);
            MPI_Bcast(&columnas, 1, MPI_UINT64_T, 0, MPI_COMM_WORLD);
            return 0;
        }

        if (fread(&filas, sizeof(uint64_t), 1, bin) != 1 ||
            fread(&columnas, sizeof(uint64_t), 1, bin) != 1) {
            printf("Error: No se pudieron leer las dimensiones.\n");
            fclose(bin);
            filas = 0;
            columnas = 0;
            MPI_Bcast(&filas, 1, MPI_UINT64_T, 0, MPI_COMM_WORLD);
            MPI_Bcast(&columnas, 1, MPI_UINT64_T, 0, MPI_COMM_WORLD);
            return 0;
        }

        if (filas == 0 || columnas == 0) {
            printf("Error: Dimensiones inválidas, (%" PRIu64 "x%" PRIu64 ").\n", filas, columnas); //NOLINT
            fclose(bin);
            MPI_Bcast(&filas, 1, MPI_UINT64_T, 0, MPI_COMM_WORLD);
            MPI_Bcast(&columnas, 1, MPI_UINT64_T, 0, MPI_COMM_WORLD);
            return 0;
        }

        temperaturas = (double *)malloc(filas * columnas * sizeof(double));
        if (!temperaturas) {
            printf("Error: No se pudo asignar memoria para la matriz.\n");
            fclose(bin);
            filas = 0;
            columnas = 0;
            MPI_Bcast(&filas, 1, MPI_UINT64_T, 0, MPI_COMM_WORLD);
            MPI_Bcast(&columnas, 1, MPI_UINT64_T, 0, MPI_COMM_WORLD);
            return 0;
        }

        if (fread(temperaturas, sizeof(double),
        (size_t)(filas * columnas), bin) != (size_t)(filas * columnas)) {
            printf("Error: No se pudieron leer los datos de temperatura.\n");
            free(temperaturas);
            fclose(bin);
            filas = 0;
            columnas = 0;
            MPI_Bcast(&filas, 1, MPI_UINT64_T, 0, MPI_COMM_WORLD);
            MPI_Bcast(&columnas, 1, MPI_UINT64_T, 0, MPI_COMM_WORLD);
            return 0;
        }

        fclose(bin);
        printf("Lectura exitosa del archivo binario (%" PRIu64 "x%" PRIu64 ").\n", filas, columnas); //NOLINT
    }

    // Broadcast de las dimensiones a todos los procesos
    MPI_Bcast(&filas, 1, MPI_UINT64_T, 0, MPI_COMM_WORLD);
    MPI_Bcast(&columnas, 1, MPI_UINT64_T, 0, MPI_COMM_WORLD);

    // Verificar si hubo error en la lectura
    if (filas == 0 || columnas == 0) {
        return 0;
    }

    // Otros procesos necesitan alocar memoria para la matriz
    if (rank != 0) {
        temperaturas = (double *)malloc(filas * columnas * sizeof(double));
        if (!temperaturas) {
            printf("Error: No se pudo asignar memoria para la matriz en proceso %d.\n", rank); //NOLINT
            return 0;
        }
    }

    // Broadcast de la matriz de temperaturas a todos los procesos
    MPI_Bcast(temperaturas, filas * columnas, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Ejecutar la simulación con MPI
    iteraciones = simular_difusion_mpi(temperaturas, filas, columnas, plate);

    // Solo el proceso 0 escribe el resultado
    if (rank == 0) {
        escribir_resultado(nombreBin, temperaturas, filas, columnas,
            iteraciones);
    }

    free(temperaturas);
    return iteraciones;
}

// Función para crear la estructura Plate a partir de una línea de texto
int crear_plate_mpi(const char *linea, const char *jobDir) {
    Plate plate;

    if (sscanf(linea, "%255s %lf %lf %lf %lf", plate.archivo_lamina,
               &plate.delta_t, &plate.alpha, &plate.h, &plate.epsilon) != 5) {
        printf("Advertencia: Línea ignorada -> %s\n", linea);
        return 0;
    }

    char rutaCompleta[512];
    snprintf(rutaCompleta, sizeof(rutaCompleta),
    "%s/%s", jobDir, plate.archivo_lamina);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        printf("\nCargando archivo binario: %s\n", rutaCompleta);
    }

    int iteraciones = leer_plate_mpi(rutaCompleta, &plate);

    if (rank == 0) {
        printf("%s procesado con éxito.\n", plate.archivo_lamina);
    }

    return iteraciones;
}
