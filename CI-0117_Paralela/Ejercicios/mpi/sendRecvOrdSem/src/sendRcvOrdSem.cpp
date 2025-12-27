#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int rank, size;
    char hostname[256];
    int token = 1;  // Token que actúa como semáforo
    MPI_Status status;
    
    // Inicializar MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Obtener el nombre del host
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        snprintf(hostname, sizeof(hostname), "unknown_host");
    }
    
    if (rank == 0) {
        // Proceso 0: saluda primero
        printf("Hello from main thread of process %d of %d on %s\n", 
               rank, size, hostname);
        fflush(stdout);
        
        // Enviar token al siguiente proceso para que pueda saludar
        if (size > 1) {
            MPI_Send(&token, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        }
        
    } else {
        // Todos los demás procesos: esperar permiso del anterior
        MPI_Recv(&token, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        
        // Imprimir saludo
        printf("Hello from main thread of process %d of %d on %s\n", 
               rank, size, hostname);
        fflush(stdout);
        
        // Dar permiso al siguiente proceso (si no es el último)
        if (rank < size - 1) {
            MPI_Send(&token, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        }
    }
    
    // Finalizar MPI
    MPI_Finalize();
    return 0;
}