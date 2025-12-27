// Copyright [2025] <Camila Rodríguez>
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <mpi.h>
#include "fileControl.h" // NOLINT
#include "plate.h"        // NOLINT
#include "report.h"       // NOLINT

#define MAX_LINE 1024
#define MAX_PLACAS 100

// Tags para comunicación MPI
#define WORK_TAG 1
#define REQUEST_TAG 2
#define RESULT_TAG 3
#define TERMINATE_TAG 4

typedef struct {
    int placa_id;
    int iteraciones;
} Resultado;

int main(int argc, char *argv[]) {
    int rank, size;
    double inicio, fin;

    // Inicializar MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    inicio = MPI_Wtime();

    if (rank == 0) {
        limpiar_directorio("resultados");
    }

    // Sincronizar todos los procesos después de limpiar
    MPI_Barrier(MPI_COMM_WORLD);

    if (argc < 2) {
        if (rank == 0) {
            printf("Uso: mpirun -np <num_procesos> %s <archivo_trabajo>\n",
                argv[0]);
        }
        MPI_Finalize();
        return 1;
    }

    // Extraer el directorio del jobPath
    char *jobPath = argv[1];
    char *jobPathCopy = strdup(jobPath);
    char *jobDir = dirname(jobPathCopy);

    if (rank == 0) {
        printf("Usando %d procesos MPI con mapeo dinámico\n", size);
        printf("Intentando abrir: '%s'\n", jobPath);
    }

    FILE *jobFile = fopen(jobPath, "r");
    if (!jobFile) {
        if (rank == 0) {
            perror("Error al abrir el archivo");
        }
        free(jobPathCopy);
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        printf("Archivo %s abierto correctamente.\n", jobPath);
    }

    // Leer todas las líneas del archivo
    char lineas[MAX_PLACAS][MAX_LINE];
    int totalPlacas = 0;
    while (fgets(lineas[totalPlacas], MAX_LINE, jobFile)) {
        lineas[totalPlacas][strcspn(lineas[totalPlacas], "\n")] = '\0';
        totalPlacas++;
    }
    fclose(jobFile);

    // Broadcast del número total de placas y las líneas a todos los procesos
    MPI_Bcast(&totalPlacas, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(lineas, MAX_PLACAS * MAX_LINE, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(jobDir, 512, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Array para almacenar iteraciones
    int iteracionesArray[MAX_PLACAS];
    for (int i = 0; i < MAX_PLACAS; i++) {
        iteracionesArray[i] = 0;
    }

    if (rank == 0) {
        // Distribuidor de trabajo dinámico
        printf("Proceso maestro iniciando distribución dinámica de "
               "trabajo...\n");

        int tarea_actual = 0;
        int trabajadores_activos = size - 1;
        int trabajadores_terminados = 0;
        MPI_Status status;
        Resultado resultado;

        // Distribuir trabajo inicial a todos los trabajadores
        for (int p = 1; p < size && tarea_actual < totalPlacas; p++) {
            printf("Asignando placa %d al proceso %d\n", tarea_actual, p);
            MPI_Send(&tarea_actual, 1, MPI_INT, p, WORK_TAG, MPI_COMM_WORLD);
            tarea_actual++;
        }

        // Ciclo principal de distribución dinámica
        while (trabajadores_terminados < trabajadores_activos) {
            // Esperar solicitud de trabajo o resultado
            MPI_Recv(&resultado, sizeof(Resultado), MPI_BYTE, MPI_ANY_SOURCE,
                    MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            if (status.MPI_TAG == RESULT_TAG) {
                // Recibir resultado de trabajo completado
                iteracionesArray[resultado.placa_id] = resultado.iteraciones;
                printf("Proceso %d completó placa %d con %d iteraciones\n",
                       status.MPI_SOURCE, resultado.placa_id,
                       resultado.iteraciones);

                // Asignar nueva tarea si hay disponibles
                if (tarea_actual < totalPlacas) {
                    printf("Asignando placa %d al proceso %d\n", tarea_actual,
                           status.MPI_SOURCE);
                    MPI_Send(&tarea_actual, 1, MPI_INT, status.MPI_SOURCE,
                            WORK_TAG, MPI_COMM_WORLD);
                    tarea_actual++;
                } else {
                    // No hay más trabajo, terminar trabajador
                    int terminar = -1;
                    MPI_Send(&terminar, 1, MPI_INT, status.MPI_SOURCE,
                            TERMINATE_TAG, MPI_COMM_WORLD);
                    trabajadores_terminados++;
                    printf("Proceso %d terminado. Trabajadores restantes: "
                           "%d\n", status.MPI_SOURCE,
                           trabajadores_activos - trabajadores_terminados);
                }
            }
        }

        printf("Todos los trabajadores han terminado. Creando reporte...\n");
        crear_reporte(jobPath, iteracionesArray);

        fin = MPI_Wtime();
        printf("Tiempo total de ejecución con mapeo dinámico: %.6f "
               "segundos\n", fin - inicio);

    } else {
        // PROCESOS TRABAJADORES
        int tarea;
        MPI_Status status;
        Resultado resultado;

        while (1) {
            // Recibir tarea del maestro
            MPI_Recv(&tarea, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD,
                     &status);

            if (status.MPI_TAG == TERMINATE_TAG) {
                // Señal de terminación
                printf("Proceso %d terminando...\n", rank);
                break;
            }

            if (status.MPI_TAG == WORK_TAG && tarea >= 0) {
                // Procesar la tarea asignada
                printf("Proceso %d procesando placa %d: %s\n", rank, tarea,
                       lineas[tarea]);

                int iteraciones = crear_plate_mpi(lineas[tarea], jobDir);

                // Enviar resultado al maestro
                resultado.placa_id = tarea;
                resultado.iteraciones = iteraciones;
                MPI_Send(&resultado, sizeof(Resultado), MPI_BYTE, 0,
                        RESULT_TAG, MPI_COMM_WORLD);

                printf("Proceso %d completó placa %d\n", rank, tarea);
            }
        }
    }

    free(jobPathCopy);
    MPI_Finalize();
    return 0;
}
