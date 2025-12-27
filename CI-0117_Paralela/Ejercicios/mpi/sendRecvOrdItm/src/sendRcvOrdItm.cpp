#include <mpi.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

#define MAX_MSG_LEN 512
#define INTERMEDIARY_RANK 0

int main(int argc, char** argv) {
    int rank, size;
    char hostname[256];
    MPI::Status status;
    
    // Inicializar MPI
    MPI::Init(argc, argv);
    rank = MPI::COMM_WORLD.Get_rank();
    size = MPI::COMM_WORLD.Get_size();
    
    // Obtener el nombre del host
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        std::strcpy(hostname, "unknown_host");
    }
    
    if (rank == INTERMEDIARY_RANK) {
        // ========== PROCESO INTERMEDIARIO ==========
        std::cout << "Intermediary process " << rank << " starting to collect greetings..." << std::endl;
        std::cout.flush();
        
        // Usar vector de strings para mayor seguridad y facilidad en C++
        std::vector<std::string> all_messages(size);
        
        // Crear el mensaje propio del intermediario
        all_messages[rank] = "Hello from main thread of process " + 
                           std::to_string(rank) + " of " + 
                           std::to_string(size) + " on " + 
                           std::string(hostname);
        
        // Buffer temporal para recibir mensajes
        char temp_buffer[MAX_MSG_LEN];
        
        // Recibir mensajes de todos los otros procesos
        for (int i = 1; i < size; i++) {
            MPI::COMM_WORLD.Recv(temp_buffer, MAX_MSG_LEN, MPI::CHAR, i, 0, status);
            all_messages[i] = std::string(temp_buffer);
        }
        
        // Imprimir todos los mensajes en orden por rank
        std::cout << "\n=== Greetings in order ===" << std::endl;
        for (int i = 0; i < size; i++) {
            std::cout << all_messages[i] << std::endl;
            std::cout.flush();
        }
        
    } else {
        // ========== PROCESOS TRABAJADORES ==========
        
        // Crear el mensaje de saludo usando string de C++
        std::string greeting_str = "Hello from main thread of process " + 
                                 std::to_string(rank) + " of " + 
                                 std::to_string(size) + " on " + 
                                 std::string(hostname);
        
        // Convertir a C-string para envío por MPI
        char message[MAX_MSG_LEN];
        std::strncpy(message, greeting_str.c_str(), MAX_MSG_LEN - 1);
        message[MAX_MSG_LEN - 1] = '\0'; // Asegurar terminación nula
        
        // Enviar el saludo al proceso intermediario
        MPI::COMM_WORLD.Send(message, std::strlen(message) + 1, MPI::CHAR, INTERMEDIARY_RANK, 0);
        
        // Confirmar que se envió el mensaje
        std::cout << "Process " << rank << " sent greeting to intermediary" << std::endl;
        std::cout.flush();
    }
    
    // Finalizar MPI
    MPI::Finalize();
    return 0;
}