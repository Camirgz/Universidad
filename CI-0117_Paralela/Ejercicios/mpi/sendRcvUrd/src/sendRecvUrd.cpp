// Copyright 2021 Jeisson Hidalgo  CC-BY 4.0
// Modificado para que los procesos saluden al intermediario en orden de recepción
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <mpi.h>

#define fail(msg) throw std::runtime_error(msg)

const size_t MESSAGE_CAPACITY = 512;

void greet(int process_number, int process_count, const char* process_hostname);

int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  if (MPI_Init(&argc, &argv) == MPI_SUCCESS) {
    int process_number = -1;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_number);
    
    int process_count = -1;
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);
    
    char process_hostname[MPI_MAX_PROCESSOR_NAME] = { '\0' };
    int hostname_length = -1;
    MPI_Get_processor_name(process_hostname, &hostname_length);
    
    try {
      greet(process_number, process_count, process_hostname);
    } catch (const std::runtime_error& exception) {
      std::cerr << "error: " << exception.what() << std::endl;
      error = EXIT_FAILURE;
    }
    
    MPI_Finalize();
  } else {
    std::cerr << "error: could not init MPI" << std::endl;
    error = EXIT_FAILURE;
  }
  return error;
}

void greet(int process_number, int process_count, const char* process_hostname) {
  // Crear mensaje de saludo
  std::stringstream buffer;
  buffer << "Hello from process " << process_number
         << " of " << process_count << " on " << process_hostname;
  
  if (process_number != 0) {
    // Los procesos trabajadores envían su saludo al proceso intermediario (proceso 0)
    const std::string& message = buffer.str();
    if (MPI_Send(message.data(), message.length() + 1, MPI_CHAR, /*target*/ 0,
                 /*tag*/ process_number, MPI_COMM_WORLD) != MPI_SUCCESS) {
      fail("could not send greeting message");
    }
    std::cout << "Process " << process_number << ": Sent greeting to intermediary process" << std::endl;
  } else {
    // El proceso intermediario (proceso 0) recibe y reporta los saludos
    std::cout << "=== INTERMEDIARY PROCESS REPORT ===" << std::endl;
    std::cout << "Intermediary process " << process_number << " on " << process_hostname << std::endl;
    std::cout << "Receiving greetings in order of arrival:" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    
    // Recibir saludos de todos los demás procesos en el orden que lleguen
    for (int received = 0; received < process_count - 1; ++received) {
      std::vector<char> message(MESSAGE_CAPACITY);
      MPI_Status status;
      
      // Usar MPI_ANY_SOURCE para recibir en orden de llegada
      if (MPI_Recv(&message[0], MESSAGE_CAPACITY, MPI_CHAR, MPI_ANY_SOURCE,
                   MPI_ANY_TAG, MPI_COMM_WORLD, &status) != MPI_SUCCESS) {
        fail("could not receive greeting message");
      }
      
      // Reportar el saludo recibido con información del orden
      std::cout << "Greeting #" << (received + 1) << " received from process " 
                << status.MPI_SOURCE << ": " << &message[0] << std::endl;
    }
    
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "All greetings received and reported!" << std::endl;
  }
}