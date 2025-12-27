// Copyright [2025] <Camila Rodríguez>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct {
    int GolpesMaximos;
    int GolpesRestantes;
    int CantidadHilos;
    pthread_mutex_t lock;
} Piñata;

typedef struct {
    int id;
    Piñata *pinata;
} DatosHilo;


void* simularGolpe(void *arg) {

    // Inicializar datos para el hilo
    DatosHilo *datos = (DatosHilo*)arg;
    Piñata *pinata = datos->pinata;
    int golpesDados = 0;

    // Simular el golpe a la piñata
    // Cada hilo intentará golpear la piñata hasta que se rompa
    while (true) {

        // Bloquear el mutex para acceder a la piñata
        pthread_mutex_lock(&pinata->lock);

        // Verificar si la piñata ya está rota
        if (pinata->GolpesRestantes <= 0) {
            pthread_mutex_unlock(&pinata->lock);
            break;
        }

        // Generar un número aleatorio entre 1 y la cantidad de golpes restantes
        int golpes = (rand() % pinata->GolpesRestantes) + 1;

        // Golpear la piñata y actualizar los golpes restantes
        pinata->GolpesRestantes -= golpes;
        golpesDados += golpes;

        // Imprimir el estado actual de la piñata si se rompe
        if (pinata->GolpesRestantes == 0) {
            printf("La piñata ha sido rota por el hilo: %d , en %d hits!\n", datos->id, golpesDados);
            pthread_mutex_unlock(&pinata->lock);
            break;
        }

        pthread_mutex_unlock(&pinata->lock);
    }

    printf("Thread %d: %d hits\n", datos->id, golpesDados);
    return NULL;
}

// Función para crear la piñata y los hilos
void crear_pinata(int golpesMaximos, int cantidadHilos) {

    // Inicializar la piñata
    Piñata pinata;
    pinata.GolpesMaximos = golpesMaximos;
    pinata.GolpesRestantes = golpesMaximos;
    pinata.CantidadHilos = cantidadHilos;
    pthread_mutex_init(&pinata.lock, NULL);

    // Crear los hilos
    pthread_t hilos[cantidadHilos];
    DatosHilo datos[cantidadHilos];

    // Inicializar los datos de cada hilo y crear los hilos
    for (int i = 0; i < cantidadHilos; i++) {
        datos[i].id = i;
        datos[i].pinata = &pinata;

        if (pthread_create(&hilos[i], NULL, simularGolpe, &datos[i]) != 0) {
            printf("Error: No se pudo crear el hilo %d.\n", i);
            return;
        }
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < cantidadHilos; i++) {
        pthread_join(hilos[i], NULL);
    }

    // Imprimir el resultado final
    pthread_mutex_destroy(&pinata.lock);
}

// Función principal
int main(int argc, char *argv[]) {

    // Verificar que se pasen los argumentos correctos
    if (argc != 3) {
        printf("Uso: %s <cantidad_hilos> <golpes_maximos>\n", argv[0]);
        return 1;
    }

    // Convertir los argumentos a enteros
    int cantidadHilos = atoi(argv[1]);
    int golpesMaximos = atoi(argv[2]);

    // Validar los argumentos
    if (cantidadHilos <= 0 || golpesMaximos <= 0) {
        printf("Los valores deben ser mayores a 0.\n");
        return 1;
    }

    srand(time(NULL));

    // Crear la piñata y los hilos
    crear_pinata(golpesMaximos, cantidadHilos);

    return 0;
}
