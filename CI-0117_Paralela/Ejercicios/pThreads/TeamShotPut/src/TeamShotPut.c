#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estructura para almacenar datos de los atletas, es como un objeto atleta
typedef struct {
    int equipo;
    int id_atleta;
    double *tabla_puntajes;
    unsigned int semilla;
} Atleta;

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

// Función principal
int main(int argc, char *argv[]) {

    // Verificar que se haya pasado un argumento
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <número de atletas>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    // Verificar que el número de atletas sea impar
    int num_atletas = atoi(argv[1]); // Convertir argumento a entero (atoi)
    if (num_atletas % 2 == 0) {
        fprintf(stderr, "Error: la cantidad de atletas debe ser impar\n");
        return EXIT_FAILURE;
    }
    
    // Inicializar semilla para números aleatorios
    srand(time(NULL)); 
    
    // Verificar que la memoria para los puntajes y hilos pueda ser reservada correctamente
    double *puntajes_equipo1 = malloc(num_atletas * sizeof(double));
    double *puntajes_equipo2 = malloc(num_atletas * sizeof(double));
    pthread_t *hilos = malloc(num_atletas * 2 * sizeof(pthread_t));
    Atleta *atletas = malloc(num_atletas * 2 * sizeof(Atleta));

    if (puntajes_equipo1 == EXIT_SUCCESS || puntajes_equipo2 == EXIT_SUCCESS || hilos == EXIT_SUCCESS || atletas == EXIT_SUCCESS) {
        fprintf(stderr, "Error al reservar memoria para los puntajes o hilos\n");
        return EXIT_FAILURE;
    }

    // Crear hilos para cada atleta del equipo 1
    for (int i = 0; i < num_atletas; i++) {
        atletas[i].equipo = 1;
        atletas[i].id_atleta = i + 1;
        atletas[i].tabla_puntajes = puntajes_equipo1;
        atletas[i].semilla = rand(); // Asignar semilla aleatoria a cada atleta
        if (pthread_create(&hilos[i], NULL, atleta_realizar, &atletas[i]) != 0) {
            fprintf(stderr, "Error al crear el hilo para el atleta %d.%d\n", atletas[i].equipo, atletas[i].id_atleta);
            return EXIT_FAILURE; // Salir si hay un error
        }
    }
    
    // Crear hilos para cada atleta del equipo 2
    for (int i = 0; i < num_atletas; i++) { 
        atletas[num_atletas + i].equipo = 2;
        atletas[num_atletas + i].id_atleta = i + 1;
        atletas[num_atletas + i].tabla_puntajes = puntajes_equipo2;
        atletas[num_atletas + i].semilla = rand(); // Asignar semilla aleatoria a cada atleta
        if (pthread_create(&hilos[num_atletas + i], NULL, atleta_realizar, &atletas[num_atletas + i]) != 0) {
            fprintf(stderr, "Error al crear el hilo para el atleta %d.%d\n", atletas[num_atletas + i].equipo, atletas[num_atletas + i].id_atleta);
            return EXIT_FAILURE; // Salir si hay un error
        }
    }
    
    // Esperar a que todos los atletas terminen
    for (int i = 0; i < num_atletas * 2; i++) { // Esperar a que todos los hilos terminen
        if (pthread_join(hilos[i], NULL) != 0) { // Verificar si hay un error al esperar el hilo
            fprintf(stderr, "Error al esperar el hilo %d\n", i);
            return EXIT_FAILURE; // Salir si hay un error
        }
    }
    
    // Determinar el equipo ganador
    int puntos_equipo1 = 0, puntos_equipo2 = 0; // Contadores de puntos
    for (int i = 0; i < num_atletas; i++) { // Comparar los puntajes de cada atleta
        if (puntajes_equipo1[i] > puntajes_equipo2[i]) {
            puntos_equipo1++;
        } else {
            puntos_equipo2++;
        }
    }
    
    // Imprimir el resultado con un print con formato
    printf("Resultado %d:%d, el equipo %d gana\n", puntos_equipo1, puntos_equipo2, 
           (puntos_equipo1 > puntos_equipo2) ? 1 : 2);
    
    // Liberar la memoria reservada
    free(puntajes_equipo1);
    free(puntajes_equipo2);
    free(hilos);
    free(atletas);

    return EXIT_SUCCESS;
}
