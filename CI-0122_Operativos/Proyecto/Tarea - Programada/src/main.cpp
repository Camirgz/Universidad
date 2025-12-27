#include "virtual_memory_system.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

int main(int argc, char* argv[]) {
    std::cout << "\nSistema de Memoria Virtual con Multiprocesamiento" << std::endl;
    std::cout << "Camila Rodríguez - Yosery Zheng Lu" << std::endl;
    std::cout << "Sistemas Operativos - 2025\n" << std::endl;
    
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " [--lru] <programa1.txt> [programa2.txt] ..." << std::endl;
        std::cerr << "Opciones:" << std::endl;
        std::cerr << "  --lru    Usar algoritmo LRU (por defecto: Enhanced Second Chance)" << std::endl;
        std::cerr << "Ejemplo: " << argv[0] << " program1.txt program2.txt" << std::endl;
        std::cerr << "Ejemplo: " << argv[0] << " --lru program1.txt program2.txt\n" << std::endl;
        return 1;
    }
    
    bool use_lru = false;
    int first_program_index = 1;
    
    if (argc > 1 && std::strcmp(argv[1], "--lru") == 0) {
        use_lru = true;
        first_program_index = 2;
    }
    
    if (argc <= first_program_index) {
        std::cerr << "Error: debe especificar al menos un archivo de programa\n" << std::endl;
        return 1;
    }
    
    VirtualMemorySystem vm_system(use_lru);
    
    std::vector<std::string> program_files;
    for (int i = first_program_index; i < argc && (int)program_files.size() < MAX_PROCESSES; i++) {
        program_files.push_back(argv[i]);
    }
    
    if (argc - first_program_index > MAX_PROCESSES) {
        std::cout << "Advertencia: máximo " << MAX_PROCESSES << " procesos permitidos.\n" << std::endl;
    }
    
    int successful_processes = 0;
    for (const std::string& program_file : program_files) {
        if (vm_system.create_process(program_file)) {
            successful_processes++;
        }
    }
    
    if (successful_processes == 0) {
        std::cerr << "Error: no se pudieron crear procesos" << std::endl;
        return 1;
    }
    
    vm_system.run_all_processes();
    vm_system.wait_all_processes();
    vm_system.print_statistics();
    
    std::cout << "\nSistema terminado exitosamente\n" << std::endl;
    
    return 0;
}