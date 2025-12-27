#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int victory_score;
    double hit_rate_p0, hit_rate_p1;
    int score_p0 = 0, score_p1 = 0;
    int round_num = 1;
    int serves_count;
    int round_winner;
    MPI_Status status;
    
    // Inicializar MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Verificar que se ejecute con exactamente 2 procesos
    if (size != 2) {
        if (rank == 0) {
            fprintf(stderr, "Error: Este programa debe ejecutarse con exactamente 2 procesos.\n");
            fprintf(stderr, "Uso: mpirun -np 2 %s <victory_score> <hit_rate_p0> <hit_rate_p1>\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }
    
    // Verificar argumentos de línea de comandos
    if (argc != 4) {
        if (rank == 0) {
            fprintf(stderr, "Error: Se requieren exactamente 3 argumentos.\n");
            fprintf(stderr, "Uso: mpirun -np 2 %s <victory_score> <hit_rate_p0> <hit_rate_p1>\n", argv[0]);
            fprintf(stderr, "Ejemplo: mpirun -np 2 %s 3 85.5 88\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }
    
    // Parsear argumentos
    victory_score = atoi(argv[1]);
    hit_rate_p0 = atof(argv[2]);
    hit_rate_p1 = atof(argv[3]);
    
    // Validar argumentos
    if (victory_score <= 0) {
        if (rank == 0) {
            fprintf(stderr, "Error: El marcador de victoria debe ser un número positivo.\n");
        }
        MPI_Finalize();
        return 1;
    }
    
    if (hit_rate_p0 < 0 || hit_rate_p0 > 100 || hit_rate_p1 < 0 || hit_rate_p1 > 100) {
        if (rank == 0) {
            fprintf(stderr, "Error: Las probabilidades de acierto deben estar entre 0 y 100.\n");
        }
        MPI_Finalize();
        return 1;
    }
    
    // Inicializar generador de números aleatorios con semillas diferentes
    srand(time(NULL) + rank);
    
    // Jugar hasta que alguien alcance el marcador de victoria
    while (score_p0 < victory_score && score_p1 < victory_score) {
        serves_count = 0;
        round_winner = -1;
        
        if (rank == 0) {
            // Proceso 0 inicia la ronda
            int ball = 1;  // 1 indica que la pelota está en juego
            serves_count = 1;
            
            // Enviar la pelota al proceso 1
            MPI_Send(&ball, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            
            // Esperar el resultado de la ronda
            MPI_Recv(&serves_count, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &status);
            MPI_Recv(&round_winner, 1, MPI_INT, 1, 2, MPI_COMM_WORLD, &status);
            
        } else if (rank == 1) {
            // Proceso 1 maneja el intercambio de la pelota
            int ball;
            int current_player = 0;  // 0 = proceso 0, 1 = proceso 1
            
            // Recibir la pelota inicial del proceso 0
            MPI_Recv(&ball, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
            serves_count = 1;
            
            // Simular el intercambio hasta que alguien falle
            while (ball > 0) {
                double random_val = (double)rand() / RAND_MAX * 100.0;
                double hit_rate = (current_player == 0) ? hit_rate_p0 : hit_rate_p1;
                
                if (random_val <= hit_rate) {
                    // Acierto - continúa el juego
                    current_player = 1 - current_player;  // Cambiar de jugador
                    serves_count++;
                    
                    if (serves_count > 1000) {  // Evitar bucles infinitos en casos extremos
                        round_winner = rand() % 2;  // Ganador aleatorio
                        break;
                    }
                } else {
                    // Fallo - el otro jugador gana la ronda
                    round_winner = 1 - current_player;
                    break;
                }
            }
            
            // Enviar resultado al proceso 0
            MPI_Send(&serves_count, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
            MPI_Send(&round_winner, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        }
        
        // Sincronizar resultados entre procesos
        MPI_Bcast(&serves_count, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&round_winner, 1, MPI_INT, 0, MPI_COMM_WORLD);
        
        // Actualizar marcador
        if (round_winner == 0) {
            score_p0++;
        } else {
            score_p1++;
        }
        
        // Imprimir resultado de la ronda (solo proceso 0 para evitar duplicados)
        if (rank == 0) {
            printf("%d: %d %d\n", round_num, serves_count, round_winner);
            fflush(stdout);
        }
        
        round_num++;
    }
    
    // Imprimir resultado final (solo proceso 0)
    if (rank == 0) {
        if (score_p0 > score_p1) {
            printf("0 wins %d to %d\n", score_p0, score_p1);
        } else if (score_p1 > score_p0) {
            printf("1 wins %d to %d\n", score_p1, score_p0);
        } else {
            printf("Tie %d to %d\n", score_p0, score_p1);
        }
    }
    
    MPI_Finalize();
    return 0;
}