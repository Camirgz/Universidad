// Copyright [2025] <Camila Rodríguez>

#include "plate.h" //NOLINT
#include "fileControl.h"  //NOLINT
#include <inttypes.h>

// Función para verificar fronteras
void copiar_boundaries(double *temperaturas,
    double *nueva_temp, uint64_t filas, uint64_t columnas) {
    // Copiar filas de arriba y abajo para los límites
    for (size_t j = 0; j < columnas; j++) {
        nueva_temp[0 * columnas + j] = temperaturas[0 * columnas + j];
        nueva_temp[(filas-1)*columnas + j]
        = temperaturas[(filas-1)*columnas + j];
    }
    // Copiar columnas de izquierda y derecha para los límites
    for (size_t i = 1; i < filas-1; i++) {
        nueva_temp[i * columnas + 0] = temperaturas[i * columnas + 0];
        nueva_temp[i * columnas + (columnas-1)] =
        temperaturas[i * columnas + (columnas-1)];
    }
}

// Función para simular la difusión térmica
int simular_difusion(double *temperaturas, uint64_t filas,
    uint64_t columnas, const Plate *plate) {

    printf("Iniciando simulación de difusión térmica\n");

    // Verificar dimensiones
    double *nueva_temp = (double *)malloc(filas * columnas * sizeof(double));  //NOLINT
    if (!nueva_temp) {
        printf("Error: No se pudo asignar memoria para la matriz temporal.\n");
        return 0;
    }

    // Inicializar variables
    int iteraciones = 0;
    double cambioMax;
    double coef = plate->alpha * plate->delta_t / (plate->h * plate->h);

    // Verificar coeficiente de estabilidad
    if (coef > 0.25) {
        printf("Coeficiente (%.6lf) puede causar inestabilidad.\n", coef);
    }

    // Inicializar simulación
    do {
        copiar_boundaries(temperaturas, nueva_temp, filas, columnas);
        cambioMax = 0.0;

        for (size_t i = 1; i < filas - 1; i++) {
            for (size_t j = 1; j < columnas - 1; j++) {
                int idx = i * columnas + j;

                double arriba = temperaturas[(i - 1) * columnas + j];
                double abajo = temperaturas[(i + 1) * columnas + j];
                double izquierda = temperaturas[i * columnas + (j - 1)];
                double derecha = temperaturas[i * columnas + (j + 1)];

                nueva_temp[idx] = temperaturas[idx] + coef *
                                   (arriba + abajo + izquierda + derecha
                                    - 4.0 * temperaturas[idx]);

                double cambio = nueva_temp[idx] - temperaturas[idx];
                if (cambio < 0) cambio = -cambio;
                if (cambio > cambioMax) cambioMax = cambio;
            }
        }

        memcpy(temperaturas, nueva_temp, filas * columnas * sizeof(double));
        iteraciones++;
    } while (cambioMax > plate->epsilon);

    printf("Difusión completada en %d iteraciones.\n", iteraciones);
    free(nueva_temp);
    return iteraciones;
}

// Función para escribir el resultado en un archivo
void leer_plate(const char *nombreBin, const Plate *plate,
    int *iteracionesArray, int *contador) {

    FILE *bin = fopen(nombreBin, "rb");
    if (!bin) {
        perror("Error al abrir el archivo binario");
        return;
    }

    uint64_t filas, columnas;
    if (fread(&filas, sizeof(u_int64_t), 1, bin) != 1 ||
        fread(&columnas, sizeof(u_int64_t), 1, bin) != 1) {
        printf("Error: No se pudieron leer las dimensiones.\n");
        fclose(bin);
        return;
    }

    if (filas == 0 || columnas == 0) {
        printf("Error: Dimensiones inválidas, (%" PRIu64 "x%" PRIu64 ").\n", filas, columnas);
        fclose(bin);
        return;
    }

    double *temperaturas = (double *)malloc(filas * columnas * sizeof(double));  //NOLINT
    if (!temperaturas) {
        printf("Error: No se pudo asignar memoria para la matriz.\n");
        fclose(bin);
        return;
    }

    if (fread(temperaturas, sizeof(double), (size_t)(filas * columnas), bin) !=
        (size_t)(filas * columnas)) {  //NOLINT
        printf("Error: No se pudieron leer los datos de temperatura.\n");
        free(temperaturas);
        fclose(bin);
        return;
    }

    fclose(bin);
    printf("Lectura exitosa del archivo binario (%" PRIu64 "x%" PRIu64 ").\n", filas, columnas);

    int iteraciones = simular_difusion(temperaturas, filas, columnas, plate);
    iteracionesArray[(*contador)] = iteraciones;
    (*contador)++;

    escribir_resultado(nombreBin, temperaturas, filas, columnas, iteraciones);
    free(temperaturas);
}

// Función para procesar una línea del archivo de entrada
void crear_plate(const char *linea, int *iteracionesArray, int *contador) {
    Plate plate;

    if (sscanf(linea, "%255s %lf %lf %lf %lf", plate.archivo_lamina,
               &plate.delta_t, &plate.alpha, &plate.h, &plate.epsilon) != 5) {
        printf("Advertencia: Línea ignorada -> %s\n", linea);
        return;
    }

    char rutaCompleta[512];
    snprintf(rutaCompleta, sizeof(rutaCompleta), "tests/%s",
    plate.archivo_lamina);

    printf("\nCargando archivo binario: %s\n", rutaCompleta);
    leer_plate(rutaCompleta, &plate, iteracionesArray, contador);
    printf("%s procesado con éxito.\n", plate.archivo_lamina);
}
