// Copyright [2025] <Camila Rodríguez>

#include "fileControl.h"

// Función para limpiar el directorio de resultados
void limpiar_directorio(const char *directorio) {
    DIR *dir = opendir(directorio);  // Abrir el directorio

    // Verificar si se pudo abrir el directorio
    if (!dir) {
        if (errno == ENOENT) {
            // Si el directorio no existe, crearlo
            mkdir(directorio, 0777);
        }
        return;
    }

    struct dirent *entrada;  // Almacenar la entrada del directorio
    // Limpiar el directorio eliminando todos los archivos
    char rutaArchivo[512];

    // Leer cada entrada del directorio
    while ((entrada = readdir(dir)) != NULL) {
        if (strcmp(entrada->d_name, ".") == 0 ||
        strcmp(entrada->d_name, "..") == 0) {
            continue;  // Ignorar "." y ".."
        }
        snprintf(rutaArchivo, sizeof(rutaArchivo), "%s/%s",
        directorio, entrada->d_name);
        unlink(rutaArchivo);  // Eliminar archivo
    }

    closedir(dir);
}

// Función para escribir el resultado en un archivo binario
void escribir_resultado(const char *nombreBin, double *temperaturas,
    uint64_t filas, uint64_t columnas, int iteraciones) {
    char nombreSalida[512];

    // Extraer el prefijo "plate001" del nombre original
    const char *nombreBase = strrchr(nombreBin, '/');  // Buscar la última '/'
    if (nombreBase) {
        nombreBase++;  // Saltar el '/'
    } else {
        nombreBase = nombreBin;  // Si no hay '/', usar el nombre completo
    }

    // Crear el nuevo nombre de archivo con iteraciones
    snprintf(nombreSalida, sizeof(nombreSalida), "resultados/%.*s-%d.bin",
    (int)(strchr(nombreBase, '.') - nombreBase), nombreBase, iteraciones);  //NOLINT

    // Crear el directorio 'resultados' si no existe
    mkdir("resultados", 0777);

    FILE *bin = fopen(nombreSalida, "wb");
    if (!bin) {
        perror("Error al abrir el archivo de salida");
        return;
    }
    fwrite(&filas, sizeof(uint64_t), 1, bin);
    fwrite(&columnas, sizeof(uint64_t), 1, bin);
    if (!bin) {
        perror("Error al abrir el archivo de salida");
        return;
    }

    // Escribir dimensiones
    fwrite(&filas, sizeof(uint64_t), 1, bin);
    fwrite(&columnas, sizeof(uint64_t), 1, bin);

    // Escribir temperaturas
    fwrite(temperaturas, sizeof(double), filas * columnas, bin);

    // Cerrar archivo
    fclose(bin);
    printf("Resultados guardados en: %s\n", nombreSalida);
}
