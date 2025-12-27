#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int ball = 0;  // La "pelota" es simplemente un entero
    int delay_ms = 0;  // Retardo en milisegundos
    MPI_Status status;
    
    // Inicializar MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Verificar que se ejecute con exactamente 2 procesos
    if (size != 2) {
        if (rank == 0) {
            fprintf(stderr, "Error: Este programa debe ejecutarse con exactamente 2 procesos.\n");
            fprintf(stderr, "Uso: mpirun -np 2 %s [delay_ms]\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }
    
    // Procesar argumento de retardo opcional
    if (argc > 1) {
        delay_ms = atoi(argv[1]);
        if (delay_ms < 0) {
            if (rank == 0) {
                fprintf(stderr, "Error: El retardo debe ser un número positivo.\n");
            }
            MPI_Finalize();
            return 1;
        }
    }
    
    // El proceso 0 inicia el juego
    if (rank == 0) {
        printf("Iniciando juego de ping-pong perfecto (Ctrl+C para terminar)\n");
        printf("Retardo: %d ms\n", delay_ms);
        printf("=====================================\n");
        fflush(stdout);
        
        // Proceso 0 sirve primero
        while (1) {
            printf("%d serves\n", rank);
            fflush(stdout);
            
            // Enviar la pelota al proceso 1
            MPI_Send(&ball, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            
            // Recibir la pelota de vuelta del proceso 1
            MPI_Recv(&ball, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
            
            // Aplicar retardo si se especificó
            if (delay_ms > 0) {
                usleep(delay_ms * 1000);  // usleep usa microsegundos
            }
        }
    }
    else if (rank == 1) {
        // Proceso 1 recibe y devuelve la pelota
        while (1) {
            // Recibir la pelota del proceso 0
            MPI_Recv(&ball, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
            
            // Aplicar retardo si se especificó
            if (delay_ms > 0) {
                usleep(delay_ms * 1000);  // usleep usa microsegundos
            }
            
            printf("%d serves\n", rank);
            fflush(stdout);
            
            // Devolver la pelota al proceso 0
            MPI_Send(&ball, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }
    
    // Finalizar MPI (este código nunca se alcanza debido al bucle infinito)
    MPI_Finalize();
    return 0;
}