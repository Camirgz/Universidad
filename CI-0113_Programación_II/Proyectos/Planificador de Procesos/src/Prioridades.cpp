#include "Prioridades.h"
#include <unistd.h> // Para sleep()

void Prioridades::ejecutar(Proceso *cabeza)
{
    // Verificar si hay procesos cargados
    if (!cabeza)
    {
        std::cout << "No hay procesos cargados.\n";
        return;
    }

    // Ordenar los procesos por prioridad (menor valor = mayor prioridad)
    for (Proceso *actual = cabeza; actual != nullptr; actual = actual->siguiente)
    {
        for (Proceso *siguiente = actual->siguiente; siguiente != nullptr; siguiente = siguiente->siguiente)
        {
            if (actual->prioridad > siguiente->prioridad)
            {
                std::swap(actual->nombre, siguiente->nombre);
                std::swap(actual->prioridad, siguiente->prioridad);
                std::swap(actual->instrucciones, siguiente->instrucciones);
            }
        }
    }

    // Imprimir procesos ordenados
    bool procesosPendientes;

    do
    {
        // Inicializar variable de control
        procesosPendientes = false;
        Proceso *actual = cabeza;

        // Imprimir estados iniciales
        while (actual)
        {
            if (!actual->instrucciones.empty())
            {
                procesosPendientes = true;

                // Cambiar estado a "En ejecución: Activo"
                actual->estado = "En ejecución: Activo";
                imprimirEstados(cabeza); // Imprimir estados después del cambio

                std::cout << MAGENTA << "\nEjecutando proceso: " << actual->nombre
                          << " (Prioridad: " << actual->prioridad << ")\n"
                          << RESET;

                std::string instruccion;
                bool bloqueadoPorES = false;

                // Ejecutar instrucciones del proceso
                while (!actual->instrucciones.empty())
                {
                    size_t pos = actual->instrucciones.find('\n');
                    if (pos == std::string::npos)
                    {
                        instruccion = actual->instrucciones;
                        actual->instrucciones.clear();
                    }
                    else
                    {
                        instruccion = actual->instrucciones.substr(0, pos);
                        actual->instrucciones = actual->instrucciones.substr(pos + 1);
                    }

                    // Verificar si la instrucción es de E/S
                    if (instruccion.find("e/s") != std::string::npos)
                    {
                        // Verificar si el proceso está bloqueado por E/S
                        if (!bloqueadoPorES)
                        {
                            actual->estado = "Bloqueado por E/S";
                            imprimirEstados(cabeza); // Imprimir estados después del cambio

                            std::cout << AMARILLO << "Proceso " << actual->nombre
                                      << " bloqueado por E/S. Ejecutando operación de E/S.\n"
                                      << RESET;
                            bloqueadoPorES = true;
                            sleep(3); // Simular tiempo de espera por E/S
                        }
                        else
                        {
                            std::cout << VERDE << "Proceso " << actual->nombre
                                      << " desbloqueado. Continuando ejecución tras operación de E/S.\n"
                                      << RESET;
                            bloqueadoPorES = false; // Desbloquear
                        }
                    }
                    else
                    { // Instrucción normal
                        if (bloqueadoPorES)
                        {
                            std::cout << VERDE << "Proceso " << actual->nombre
                                      << " desbloqueado. Continuando ejecución.\n"
                                      << RESET;
                            bloqueadoPorES = false; // Desbloquear si no está en operación de E/S
                        }

                        // Simular ejecución de instrucción
                        std::cout << "Ejecutando: " << instruccion << "\n";
                        std::cout << CYAN << "Simulando instrucción normal (1 ciclo)...\n"
                                  << RESET;
                        sleep(1);
                    }
                }

                // Cambiar estado a "Finalizado" si no hay más instrucciones
                if (actual->instrucciones.empty())
                {
                    actual->estado = "Finalizado";
                    imprimirEstados(cabeza); // Imprimir estados después del cambio

                    std::cout << VERDE << "\nProceso " << actual->nombre << " finalizado (Estado: "
                              << actual->estado << ").\n"
                              << RESET;
                }
            }
            actual = actual->siguiente;
        }

    } while (procesosPendientes);

    std::cout << "\nTodos los procesos han sido ejecutados en orden de prioridad.\n";
}
