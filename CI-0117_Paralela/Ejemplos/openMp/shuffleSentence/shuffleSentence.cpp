// shuffle_sentence.cpp
#include <omp.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    const int thread_count = argc >= 2 ? atoi(argv[1]) : omp_get_max_threads();
    std::string palabra;
    std::vector<std::string> palabras;

    // Leer todas las palabras desde la entrada estándar
    while (std::cin >> palabra) {
        palabras.push_back(palabra);
    }

#pragma omp parallel num_threads(thread_count)
#pragma omp single
    {
        if (!palabras.empty()) {
            // Imprimir la primera palabra (como tarea obligatoria primero)
#pragma omp task
            {
#pragma omp critical
                std::cout << palabras[0];
            }

            // Crear tareas para imprimir el resto de las palabras
            for (size_t i = 1; i < palabras.size(); ++i) {
#pragma omp task firstprivate(i)
                {
#pragma omp critical
                    std::cout << " " << palabras[i];
                }
            }

#pragma omp taskwait  // Esperar que todas las tareas anteriores terminen

            // Tarea para imprimir el punto final
#pragma omp task
            {
#pragma omp critical
                std::cout << "." << std::endl;
            }
        } else {
#pragma omp task
            {
                std::cout << "." << std::endl;
            }
        }
    }

    return 0;
}
