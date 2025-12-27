#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estructura para almacenar datos de los atletas
typedef struct {
    int equipo;
    int id_atleta;
    double *tabla_puntajes;
    unsigned int semilla;
} Atleta;

// Estructura para datos privados de los hilos
typedef struct {
    size_t numeroHilos;
    size_t cantidadHilos;
    void *dato;
    pthread_t numHilo;
} ThreadData;

// Función para generar un número aleatorio con semilla (creada en el grandma lottery)
void* generarNumeroAleatorio(void* semilla) {
    unsigned int* s = (unsigned int*)semilla; // Convertir la semilla a unsigned int
    int* numero = malloc(sizeof(int)); // Reservar memoria para el número aleatorio
    if (numero == NULL) { // Verificar que la memoria fue reservada correctamente
        fprintf(stderr, "Error al reservar memoria para el número aleatorio\n");
        pthread_exit(NULL); // Salir si ocurre un error
    }
    *numero = rand_r(s) % 101; // Generar un número aleatorio entre 0 y 100
    return numero; // Devolver el número aleatorio generado
}

// Función que simula los lanzamientos de un atleta
void *atleta_realizar(void *arg) {

    // Casting de argumento a estructura Atleta
    Atleta *atleta = (Atleta *)arg;
    double mejor_lanzamiento = 0.0;
    
    // Realizar 3 lanzamientos y guardar el mejor
    for (int i = 0; i < 3; i++) {
        int* lanzamiento_int = generarNumeroAleatorio(&atleta->semilla); // Llamar a la función para generar el número aleatorio
        if (lanzamiento_int == NULL) { // Verificar si la generación del número aleatorio fue exitosa
            return NULL; // Salir si hay un error
        }
        double lanzamiento = (*lanzamiento_int / 100.0) * 25.0; // Convertir el número aleatorio a una distancia válida
        free(lanzamiento_int); // Liberar la memoria reservada por el número aleatorio
        
        if (lanzamiento > mejor_lanzamiento) {
            mejor_lanzamiento = lanzamiento;
        }
    }
    
    // Imprimir el mejor lanzamiento
    printf("%d.%d: mejor lanzamiento %.3fm\n", atleta->equipo, atleta->id_atleta, mejor_lanzamiento); // Imprimir con formato 
    atleta->tabla_puntajes[atleta->id_atleta - 1] = mejor_lanzamiento;
    pthread_exit(NULL); 
}

// Función para crear hilos (Jeisson)
ThreadData* create_threads(size_t count, void*(*routine)(void*), void* dato) {
    ThreadData* thread_data = (ThreadData*)calloc(count, sizeof(ThreadData));
    if (!thread_data) return NULL;
    
    for (size_t i = 0; i < count; ++i) {
        thread_data[i].numeroHilos = i;
        thread_data[i].cantidadHilos = count;
        thread_data[i].dato = (Atleta*)dato + i;
        if (pthread_create(&thread_data[i].numHilo, NULL, routine, &thread_data[i]) != 0) {
            fprintf(stderr, "Error al crear el hilo %zu\n", i);
            free(thread_data);
            return NULL;
        }
    }
    return thread_data;
}

// Función para unir hilos (Jeisson)
int join_threads(size_t count, ThreadData* thread_data) {
    int error_count = 0;
    for (size_t i = 0; i < count; ++i) {
        if (pthread_join(thread_data[i].numHilo, NULL) != 0) {
            fprintf(stderr, "Error al unir el hilo %zu\n", i);
            ++error_count;
        }
    }
    free(thread_data);
    return error_count;
}

// Función principal
int main(int argc, char *argv[]) {

    // Verificar que se haya pasado un argumento
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <número de atletas>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Verificar que el número de atletas sea impar
    int num_atletas = atoi(argv[1]);
    if (num_atletas % 2 == 0) {
        fprintf(stderr, "Error: la cantidad de atletas debe ser impar\n");
        return EXIT_FAILURE;
    }

    // Inicializar semilla para números aleatorios
    srand(time(NULL));

    // Verificar que la memoria para los puntajes y hilos pueda ser reservada correctamente
    double *puntajes_equipo1 = malloc(num_atletas * sizeof(double));
    double *puntajes_equipo2 = malloc(num_atletas * sizeof(double));
    Atleta *atletas = malloc(num_atletas * 2 * sizeof(Atleta));

    if (!puntajes_equipo1 || !puntajes_equipo2 || !atletas) {
        fprintf(stderr, "Error al reservar memoria\n");
        return EXIT_FAILURE;
    }

    // Crear hilos para cada atleta del equipo 
    for (int i = 0; i < num_atletas; i++) {
        atletas[i] = (Atleta){1, i + 1, puntajes_equipo1, rand()};
        atletas[num_atletas + i] = (Atleta){2, i + 1, puntajes_equipo2, rand()};
    }

    // Crear hilos para cada atleta del equipo 1 y 2
    ThreadData *threads = create_threads(num_atletas * 2, atleta_realizar, atletas);
    if (!threads) return EXIT_FAILURE;
    join_threads(num_atletas * 2, threads);

    // Determinar el equipo ganador
    int puntos_equipo1 = 0, puntos_equipo2 = 0;
    for (int i = 0; i < num_atletas; i++) {
        if (puntajes_equipo1[i] > puntajes_equipo2[i]) {
            puntos_equipo1++;
        } else {
            puntos_equipo2++;
        }
    }

    // Imprimir el resultado con un print con formato
    printf("Resultado %d:%d, el equipo %d gana\n", puntos_equipo1, puntos_equipo2, 
           (puntos_equipo1 > puntos_equipo2) ? 1 : 2);
    
    // Liberar memoria reservada
    free(puntajes_equipo1);
    free(puntajes_equipo2);
    free(atletas);
    return EXIT_SUCCESS;
}