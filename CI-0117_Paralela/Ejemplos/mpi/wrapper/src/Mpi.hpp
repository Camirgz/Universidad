/// @file Mpi.hpp
/// @brief Clase que encapsula la inicialización y finalización de MPI con manejo de errores
#pragma once

#include <mpi.h>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @class Mpi
 * @brief Encapsula la funcionalidad básica de MPI para ejecución distribuida.
 *
 * Maneja la inicialización, finalización y atributos comunes de MPI como el número
 * de proceso, el número total de procesos y el nombre del host.
 */
class Mpi {
private:
  /// Número del proceso actual (rank)
  int process_number = -1;

  /// Cantidad total de procesos
  int process_count = -1;

  /// Nombre del host donde corre el proceso
  std::string hostname;

public:
  /**
   * @brief Constructor que inicializa el entorno MPI
   * @param argc Referencia al número de argumentos de línea de comando
   * @param argv Referencia al vector de argumentos de línea de comando
   * @throws std::runtime_error Si falla la inicialización o la obtención de datos de MPI
   */
  Mpi(int& argc, char**& argv) {
    if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
      throw std::runtime_error("No se pudo inicializar el entorno MPI");
    }

    if (MPI_Comm_rank(MPI_COMM_WORLD, &this->process_number) != MPI_SUCCESS) {
      throw std::runtime_error("No se pudo obtener el número del proceso (rank)");
    }

    if (MPI_Comm_size(MPI_COMM_WORLD, &this->process_count) != MPI_SUCCESS) {
      throw std::runtime_error("No se pudo obtener la cantidad de procesos");
    }

    char name[MPI_MAX_PROCESSOR_NAME];
    int length = 0;
    if (MPI_Get_processor_name(name, &length) != MPI_SUCCESS) {
      throw std::runtime_error("No se pudo obtener el nombre del procesador");
    }

    this->hostname = std::string(name, length);
  }

  /**
   * @brief Destructor que finaliza el entorno MPI
   */
  ~Mpi() noexcept {
    MPI_Finalize();
  }

  /// @brief Obtiene el número de proceso (rank)
  /// @return Número de proceso
  inline int getProcessNumber() const { return this->process_number; }

  /// @brief Obtiene la cantidad total de procesos
  /// @return Cantidad de procesos
  inline int getProcessCount() const { return this->process_count; }

  /// @brief Obtiene el nombre del host donde corre el proceso
  /// @return Nombre del host
  inline const std::string& getHostname() const { return this->hostname; }

  /// @brief Acceso alternativo al número de proceso (rank)
  inline int rank() const { return this->getProcessNumber(); }

  /// @brief Acceso alternativo a la cantidad de procesos
  inline int size() const { return this->getProcessCount(); }
};
