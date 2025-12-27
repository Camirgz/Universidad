#include "virtual_memory_system.h"
#include <iostream>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <fstream>


// IMPLEMENTACIÓN: EnhancedSecondChance


EnhancedSecondChance::EnhancedSecondChance(PhysicalMemory* mem) 
    : clock_hand(0), physical_memory(mem) {
}

void EnhancedSecondChance::register_page_table(int process_id, PageTable* pt) {
    page_tables[process_id] = pt;
}

int EnhancedSecondChance::classify_page(bool reference, bool dirty) {
    // Clase 0: R=0, D=0 (no referenciada, no modificada) - Mejor víctima
    // Clase 1: R=0, D=1 (no referenciada, modificada) - Segunda opción
    // Clase 2: R=1, D=0 (referenciada, no modificada) - Dar segunda oportunidad
    // Clase 3: R=1, D=1 (referenciada, modificada) - Peor víctima
    
    if (!reference && !dirty) return 0;
    if (!reference && dirty) return 1;
    if (reference && !dirty) return 2;
    return 3; // reference && dirty
}

int EnhancedSecondChance::select_victim() {
    int victim = -1;
    int passes = 0;
    int max_passes = 4; // Máximo 4 pasadas
    
    while (passes < max_passes && victim == -1) {
        // Buscar clase objetivo según la pasada
        int target_class = (passes == 0 || passes == 2) ? 0 : 1;
        
        for (int i = 0; i < NUM_FRAMES && victim == -1; i++) {
            FrameInfo* frame_info = physical_memory->get_frame_info(clock_hand);
            
            if (!frame_info->is_free) {
                int pid = frame_info->process_id;
                uint8_t vpn = frame_info->vpn;
                
                if (page_tables.find(pid) != page_tables.end()) {
                    PageTable* pt = page_tables[pid];
                    PageTableEntry* pte = pt->get_entry(vpn);
                    
                    if (pte != nullptr) {
                        int page_class = classify_page(pte->reference, pte->dirty);
                        
                        if (page_class == target_class) {
                            // Encontramos una víctima de la clase objetivo
                            victim = clock_hand;
                        } else if (page_class >= 2) {
                            // Dar segunda oportunidad: limpiar bit R
                            pt->set_reference_bit(vpn, false);
                        }
                    }
                }
            }
            
            // Avanzar el reloj
            clock_hand = (clock_hand + 1) % NUM_FRAMES;
        }
        
        passes++;
    }
    
    // Si no encontramos víctima después de todas las pasadas, usar el frame actual
    if (victim == -1) {
        victim = clock_hand;
        clock_hand = (clock_hand + 1) % NUM_FRAMES;
    }
    
    return victim;
}

void EnhancedSecondChance::get_victim_info(int frame, int& pid, uint8_t& vpn, bool& is_dirty) {
    FrameInfo* frame_info = physical_memory->get_frame_info(frame);
    pid = frame_info->process_id;
    vpn = frame_info->vpn;
    
    if (page_tables.find(pid) != page_tables.end()) {
        PageTable* pt = page_tables[pid];
        PageTableEntry* pte = pt->get_entry(vpn);
        if (pte != nullptr) {
            is_dirty = pte->dirty;
        } else {
            is_dirty = false;
        }
    } else {
        is_dirty = false;
    }
}


// IMPLEMENTACIÓN: PhysicalMemory


PhysicalMemory::PhysicalMemory() : esc_algorithm(nullptr), lru_algorithm(nullptr), use_lru(false), free_frame_count(NUM_FRAMES) {
    pthread_mutex_init(&memory_mutex, nullptr);
    
    memset(memory, 0, PHYSICAL_MEMORY_SIZE);
    
    for (int i = 0; i < NUM_FRAMES; i++) {
        frames[i] = FrameInfo();
    }
}

PhysicalMemory::~PhysicalMemory() {
    pthread_mutex_destroy(&memory_mutex);
}

void PhysicalMemory::set_replacement_algorithm(EnhancedSecondChance* esc, LRUReplacement* lru, bool use_lru_mode) {
    esc_algorithm = esc;
    lru_algorithm = lru;
    use_lru = use_lru_mode;
}

int PhysicalMemory::get_free_frame() {
    pthread_mutex_lock(&memory_mutex);
    
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (frames[i].is_free) {
            pthread_mutex_unlock(&memory_mutex);
            return i;
        }
    }
    
    pthread_mutex_unlock(&memory_mutex);
    return -1; // No hay frames libres
}

int PhysicalMemory::allocate_frame(int process_id, uint8_t vpn) {
    pthread_mutex_lock(&memory_mutex);
    
    int frame_num = -1;
    bool was_free = false;
    
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (frames[i].is_free) {
            frame_num = i;
            was_free = true;
            break;
        }
    }
    
    pthread_mutex_unlock(&memory_mutex);
    
    if (frame_num == -1) {
        if (use_lru && lru_algorithm != nullptr) {
            frame_num = lru_algorithm->select_victim();
        } else if (!use_lru && esc_algorithm != nullptr) {
            frame_num = esc_algorithm->select_victim();
        }
        
        if (frame_num != -1) {
            int victim_pid;
            uint8_t victim_vpn;
            bool is_dirty;
            
            if (use_lru && lru_algorithm != nullptr) {
                lru_algorithm->get_victim_info(frame_num, victim_pid, victim_vpn, is_dirty);
            } else if (!use_lru && esc_algorithm != nullptr) {
                esc_algorithm->get_victim_info(frame_num, victim_pid, victim_vpn, is_dirty);
            }
            
            if (is_dirty) {
                write_page_to_disk(frame_num, victim_pid, victim_vpn);
            }
            
            was_free = false;
        }
    }
    
    pthread_mutex_lock(&memory_mutex);
    
    if (frame_num != -1) {
        frames[frame_num].is_free = false;
        frames[frame_num].process_id = process_id;
        frames[frame_num].vpn = vpn;
        
        if (was_free) {
            free_frame_count--;
        }
    }
    
    pthread_mutex_unlock(&memory_mutex);
    return frame_num;
}

void PhysicalMemory::free_frame(int frame_num) {
    if (frame_num < 0 || frame_num >= NUM_FRAMES) {
        return;
    }
    
    pthread_mutex_lock(&memory_mutex);
    
    if (!frames[frame_num].is_free) {
        frames[frame_num].is_free = true;
        frames[frame_num].process_id = -1;
        frames[frame_num].vpn = 0;
        free_frame_count++;
    }
    
    pthread_mutex_unlock(&memory_mutex);
}

uint8_t PhysicalMemory::read_byte(uint16_t physical_address) {
    if (physical_address >= PHYSICAL_MEMORY_SIZE) {
        std::cerr << "Error: Physical address out of bounds: " << physical_address << std::endl;
        return 0;
    }
    
    pthread_mutex_lock(&memory_mutex);
    uint8_t value = memory[physical_address];
    
    if (use_lru && lru_algorithm != nullptr) {
        int frame_num = physical_address / FRAME_SIZE;
        pthread_mutex_unlock(&memory_mutex);
        lru_algorithm->update_access_time(frame_num);
    } else {
        pthread_mutex_unlock(&memory_mutex);
    }
    
    return value;
}

void PhysicalMemory::write_byte(uint16_t physical_address, uint8_t value) {
    if (physical_address >= PHYSICAL_MEMORY_SIZE) {
        std::cerr << "Error: Physical address out of bounds: " << physical_address << std::endl;
        return;
    }
    
    pthread_mutex_lock(&memory_mutex);
    memory[physical_address] = value;
    
    if (use_lru && lru_algorithm != nullptr) {
        int frame_num = physical_address / FRAME_SIZE;
        pthread_mutex_unlock(&memory_mutex);
        lru_algorithm->update_access_time(frame_num);
    } else {
        pthread_mutex_unlock(&memory_mutex);
    }
}

void PhysicalMemory::load_page_from_disk(int frame_num, int process_id, uint8_t vpn, const std::string& program_file) {
    if (frame_num < 0 || frame_num >= NUM_FRAMES) {
        return;
    }
    
    pthread_mutex_lock(&memory_mutex);
    
    uint16_t start_address = frame_num * FRAME_SIZE;
    
    std::string swap_file = "swap_" + std::to_string(process_id) + ".bin";
    std::ifstream swap(swap_file, std::ios::binary);
    
    if (swap.is_open()) {
        swap.seekg(vpn * FRAME_SIZE);
        swap.read(reinterpret_cast<char*>(&memory[start_address]), FRAME_SIZE);
        
        if (swap.gcount() == FRAME_SIZE) {
            pthread_mutex_unlock(&memory_mutex);
            swap.close();
            return;
        }
        swap.close();
    }
    
    std::ifstream file(program_file);
    if (file.is_open()) {
        std::string line;
        int byte_offset = vpn * PAGE_SIZE;
        int bytes_read = 0;
        int current_byte = 0;
        
        while (std::getline(file, line) && bytes_read < FRAME_SIZE) {
            for (size_t i = 0; i < line.length() && bytes_read < FRAME_SIZE; i++) {
                if (current_byte >= byte_offset && current_byte < byte_offset + FRAME_SIZE) {
                    memory[start_address + bytes_read] = static_cast<uint8_t>(line[i]);
                    bytes_read++;
                }
                current_byte++;
            }
            if (current_byte >= byte_offset && bytes_read < FRAME_SIZE) {
                memory[start_address + bytes_read] = '\n';
                bytes_read++;
                current_byte++;
            }
        }
        
        while (bytes_read < FRAME_SIZE) {
            memory[start_address + bytes_read] = 0;
            bytes_read++;
        }
        
        file.close();
    } else {
        for (int i = 0; i < FRAME_SIZE; i++) {
            memory[start_address + i] = (vpn * 16 + process_id * 3 + i) % 256;
        }
    }
    
    pthread_mutex_unlock(&memory_mutex);
}

void PhysicalMemory::write_page_to_disk(int frame_num, int process_id, uint8_t vpn) {
    if (frame_num < 0 || frame_num >= NUM_FRAMES) {
        return;
    }
    
    std::string swap_file = "swap_" + std::to_string(process_id) + ".bin";
    std::fstream file;
    
    file.open(swap_file, std::ios::binary | std::ios::in | std::ios::out);
    if (!file) {
        file.open(swap_file, std::ios::binary | std::ios::out);
        if (!file) {
            return;
        }
    }
    
    pthread_mutex_lock(&memory_mutex);
    
    uint16_t start_address = frame_num * FRAME_SIZE;
    file.seekp(vpn * FRAME_SIZE);
    file.write(reinterpret_cast<const char*>(&memory[start_address]), FRAME_SIZE);
    file.flush();
    
    pthread_mutex_unlock(&memory_mutex);
    
    file.close();
}

FrameInfo* PhysicalMemory::get_frame_info(int frame_num) {
    if (frame_num < 0 || frame_num >= NUM_FRAMES) {
        return nullptr;
    }
    return &frames[frame_num];
}

std::vector<int> PhysicalMemory::get_process_frames(int process_id) {
    std::vector<int> process_frames;
    
    pthread_mutex_lock(&memory_mutex);
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (!frames[i].is_free && frames[i].process_id == process_id) {
            process_frames.push_back(i);
        }
    }
    pthread_mutex_unlock(&memory_mutex);
    
    return process_frames;
}

void PhysicalMemory::print_memory_status() {
    pthread_mutex_lock(&memory_mutex);
    
    std::cout << "\n=== Estado de Memoria Física ===" << std::endl;
    std::cout << "Frame | Estado | PID | VPN" << std::endl;
    std::cout << "------+--------+-----+----" << std::endl;
    
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (!frames[i].is_free) {
            std::cout << std::setw(5) << i << " | ";
            std::cout << std::setw(6) << "Usado" << " | ";
            std::cout << std::setw(3) << frames[i].process_id << " | ";
            std::cout << std::setw(3) << (int)frames[i].vpn << std::endl;
        }
    }
    
    std::cout << "\nFrames Libres: " << free_frame_count << "/" << NUM_FRAMES << std::endl;
    
    pthread_mutex_unlock(&memory_mutex);
}


// IMPLEMENTACIÓN: LRUReplacement


LRUReplacement::LRUReplacement(PhysicalMemory* mem) : physical_memory(mem), global_time(0) {
    pthread_mutex_init(&lru_mutex, nullptr);
}

LRUReplacement::~LRUReplacement() {
    pthread_mutex_destroy(&lru_mutex);
}

void LRUReplacement::register_page_table(int process_id, PageTable* pt) {
    page_tables[process_id] = pt;
}

void LRUReplacement::update_access_time(int frame) {
    pthread_mutex_lock(&lru_mutex);
    frame_access_time[frame] = global_time++;
    pthread_mutex_unlock(&lru_mutex);
}

int LRUReplacement::select_victim() {
    pthread_mutex_lock(&lru_mutex);
    
    int victim = -1;
    uint32_t oldest_time = UINT32_MAX;
    
    for (int i = 0; i < NUM_FRAMES; i++) {
        FrameInfo* frame_info = physical_memory->get_frame_info(i);
        
        if (!frame_info->is_free) {
            uint32_t access_time = frame_access_time.count(i) ? frame_access_time[i] : 0;
            
            if (access_time < oldest_time) {
                oldest_time = access_time;
                victim = i;
            }
        }
    }
    
    pthread_mutex_unlock(&lru_mutex);
    return victim;
}

void LRUReplacement::get_victim_info(int frame, int& pid, uint8_t& vpn, bool& is_dirty) {
    FrameInfo* frame_info = physical_memory->get_frame_info(frame);
    pid = frame_info->process_id;
    vpn = frame_info->vpn;
    
    if (page_tables.find(pid) != page_tables.end()) {
        PageTable* pt = page_tables[pid];
        PageTableEntry* pte = pt->get_entry(vpn);
        if (pte != nullptr) {
            is_dirty = pte->dirty;
        } else {
            is_dirty = false;
        }
    } else {
        is_dirty = false;
    }
}