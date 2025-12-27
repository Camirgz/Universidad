#include "virtual_memory_system.h"
#include <iostream>
#include <iomanip>

pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;

VirtualMemorySystem::VirtualMemorySystem(bool use_lru_mode) : next_process_id(0), use_lru(use_lru_mode) {
    physical_memory = new PhysicalMemory();
    mmu = new MMU(physical_memory);
    esc_algorithm = new EnhancedSecondChance(physical_memory);
    lru_algorithm = new LRUReplacement(physical_memory);
    physical_memory->set_replacement_algorithm(esc_algorithm, lru_algorithm, use_lru);
    
    pthread_mutex_lock(&print_mutex);
    std::cout << "=== Sistema de Memoria Virtual Inicializado ===" << std::endl;
    std::cout << "Memoria Física: " << PHYSICAL_MEMORY_SIZE << " bytes" << std::endl;
    std::cout << "Frames: " << NUM_FRAMES << " x " << FRAME_SIZE << " bytes" << std::endl;
    std::cout << "Procesos Máximos: " << MAX_PROCESSES << std::endl;
    std::cout << "TLB: " << TLB_SIZE << " entradas" << std::endl;
    std::cout << "Caché de Datos: " << DATA_CACHE_SIZE << " entradas x " 
             << CACHE_BLOCK_SIZE << " bytes" << std::endl;
    std::cout << "Algoritmo de Reemplazo: " << (use_lru ? "LRU" : "Enhanced Second Chance") << "\n" << std::endl;
    pthread_mutex_unlock(&print_mutex);
}

VirtualMemorySystem::~VirtualMemorySystem() {
    cleanup();
    delete lru_algorithm;
    delete esc_algorithm;
    delete mmu;
    delete physical_memory;
}

bool VirtualMemorySystem::create_process(const std::string& program_file) {
    if (processes.size() >= MAX_PROCESSES) {
        pthread_mutex_lock(&print_mutex);
        std::cerr << "Error: número máximo de procesos alcanzado" << std::endl;
        pthread_mutex_unlock(&print_mutex);
        return false;
    }
    
    int pid = next_process_id++;
    Process* process = new Process(pid, mmu, program_file);
    
    esc_algorithm->register_page_table(pid, process->get_page_table());
    lru_algorithm->register_page_table(pid, process->get_page_table());
    
    if (!process->load_program()) {
        delete process;
        return false;
    }
    
    processes.push_back(process);
    
    pthread_mutex_lock(&print_mutex);
    std::cout << "Proceso " << pid << " creado desde " << program_file << std::endl;
    pthread_mutex_unlock(&print_mutex);
    
    return true;
}

void* VirtualMemorySystem::thread_runner(void* arg) {
    Process* process = static_cast<Process*>(arg);
    process->run();
    return nullptr;
}

void VirtualMemorySystem::run_all_processes() {
    pthread_mutex_lock(&print_mutex);
    std::cout << "\n=== Ejecutando Procesos ===" << std::endl;
    pthread_mutex_unlock(&print_mutex);
    
    for (Process* process : processes) {
        pthread_t thread;
        if (pthread_create(&thread, nullptr, thread_runner, process) == 0) {
            thread_ids.push_back(thread);
            pthread_mutex_lock(&print_mutex);
            std::cout << "Thread iniciado para Proceso " << process->get_pid() << std::endl;
            pthread_mutex_unlock(&print_mutex);
        } else {
            pthread_mutex_lock(&print_mutex);
            std::cerr << "Error al crear thread para Proceso " << process->get_pid() << std::endl;
            pthread_mutex_unlock(&print_mutex);
        }
    }
}

void VirtualMemorySystem::wait_all_processes() {
    for (pthread_t thread : thread_ids) {
        pthread_join(thread, nullptr);
    }
    pthread_mutex_lock(&print_mutex);
    std::cout << "\n=== Todos los Procesos Completados ===\n" << std::endl;
    pthread_mutex_unlock(&print_mutex);
}

void VirtualMemorySystem::print_statistics() {
    std::cout << "========================================" << std::endl;
    std::cout << "       ESTADÍSTICAS DEL SISTEMA" << std::endl;
    std::cout << "========================================" << std::endl;
    
    int page_faults, total_accesses;
    double pf_rate;
    mmu->get_statistics(page_faults, total_accesses, pf_rate);
    
    std::cout << "\nMMU:" << std::endl;
    std::cout << "  Accesos a Memoria: " << total_accesses << std::endl;
    std::cout << "  Page Faults: " << page_faults << std::endl;
    std::cout << "  Tasa de Page Faults: " << std::fixed << std::setprecision(2) 
              << pf_rate << "%" << std::endl;
    
    int tlb_hits, tlb_misses;
    double tlb_hit_rate;
    mmu->get_tlb()->get_statistics(tlb_hits, tlb_misses, tlb_hit_rate);
    
    std::cout << "\nTLB:" << std::endl;
    std::cout << "  Hits: " << tlb_hits << std::endl;
    std::cout << "  Misses: " << tlb_misses << std::endl;
    std::cout << "  Tasa de Hits: " << std::fixed << std::setprecision(2) 
              << tlb_hit_rate << "%" << std::endl;
    
    int cache_hits, cache_misses;
    double cache_hit_rate;
    mmu->get_data_cache()->get_statistics(cache_hits, cache_misses, cache_hit_rate);
    
    std::cout << "\nCaché de Datos:" << std::endl;
    std::cout << "  Hits: " << cache_hits << std::endl;
    std::cout << "  Misses: " << cache_misses << std::endl;
    std::cout << "  Tasa de Hits: " << std::fixed << std::setprecision(2) 
              << cache_hit_rate << "%" << std::endl;
    
    physical_memory->print_memory_status();
    
    std::cout << "========================================" << std::endl;
}

void VirtualMemorySystem::cleanup() {
    for (Process* process : processes) {
        delete process;
    }
    processes.clear();
    thread_ids.clear();
}
