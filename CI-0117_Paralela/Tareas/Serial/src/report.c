// Copyright [2025] <Camila Rodríguez>

#include <time.h>
#include <stdio.h>

#include "report.h" //NOLINT
#include "fileControl.h"  //NOLINT
#include "plate.h"  //NOLINT


// Formatear el tiempo como medida: YYYY/MM/DD HH:MM:SS
char* format_time(const time_t seconds, char* text, const size_t capacity) {
    const struct tm* gmt = gmtime(&seconds);  //NOLINT
    snprintf(text, capacity, "%04d/%02d/%02d\t%02d:%02d:%02d",
        gmt->tm_year - 70,   // Años desde 0000
        gmt->tm_mon,         // Meses desde 00
        gmt->tm_mday - 1,    // Días desde 00
        gmt->tm_hour,
        gmt->tm_min,
        gmt->tm_sec);
    return text;
}

// Crear un reporte con los resultados de la simulación
void crear_reporte(const char *jobPath, int *iteracionesArray) {
    FILE *jobFile = fopen(jobPath, "r");
    FILE *reporteFile = fopen("reporte.txt", "w");

    if (!jobFile) {
        perror("Error al abrir el archivo de trabajo");
        return;
    }
    if (!reporteFile) {
        perror("Error al abrir el archivo de reporte");
        fclose(jobFile);
        return;
    }

    char linea[256];
    int index = 0;

    while (fgets(linea, sizeof(linea), jobFile)) {
        char archivo[256];
        double delta_t, alpha, h, epsilon;

        if (sscanf(linea, "%255s %lf %lf %lf %le", archivo, &delta_t,
            &alpha, &h, &epsilon) != 5) {
            printf("Advertencia: Línea ignorada por formato -> %s\n", linea);
            continue;
        }

        // Calcular tiempo simulado
        double tiempo_simulado = delta_t * iteracionesArray[index];
        time_t tiempo_transcurrido = (time_t)(tiempo_simulado);

        // Formatear el tiempo simulado
        char tiempo_formateado[48];
        format_time(tiempo_transcurrido, tiempo_formateado,
            sizeof(tiempo_formateado));

        // Escribir en el reporte
        fprintf(reporteFile, "%s\t%.0lf\t%.2lf\t%.0lf\t%.4e\t%d\t%s\n",
            archivo, delta_t, alpha, h, epsilon,
            iteracionesArray[index], tiempo_formateado);

        index++;
    }

    fclose(jobFile);
    fclose(reporteFile);
    printf("\nReporte generado en 'reporte.txt'\n");
}
