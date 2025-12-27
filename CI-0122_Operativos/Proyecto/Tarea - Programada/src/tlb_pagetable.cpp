#include "virtual_memory_system.h"
#include <iostream>
#include <cstring>
#include <iomanip>

TLB::TLB() : global_lru_counter(0), hits(0), misses(0) {
    pthread_mutex_init(&tlb_mutex, nullptr);
    for (int i = 0; i < TLB_SIZE; i++) {
        entries[i] = TLBEntry();
    }
}

TLB::~TLB() {
    pthread_mutex_destroy(&tlb_mutex);
}

bool TLB::lookup(int process_id, uint8_t vpn, uint8_t& frame) {
    pthread_mutex_lock(&tlb_mutex);
    
    for (int i = 0; i < TLB_SIZE; i++) {
        if (entries[i].valid && 
            entries[i].process_id == process_id && 
            entries[i].vpn == vpn) {
            // TLB Hit
            frame = entries[i].frame;
            entries[i].lru_counter = global_lru_counter++;
            hits++;
            pthread_mutex_unlock(&tlb_mutex);
            return true;
        }
    }
    
    // TLB Miss
    misses++;
    pthread_mutex_unlock(&tlb_mutex);
    return false;
}

void TLB::insert(int process_id, uint8_t vpn, uint8_t frame) {
    pthread_mutex_lock(&tlb_mutex);
    
    // Buscar entrada inválida o usar LRU
    int victim_index = -1;
    uint32_t min_lru = UINT32_MAX;
    
    for (int i = 0; i < TLB_SIZE; i++) {
        if (!entries[i].valid) {
            victim_index = i;
            break;
        }
        if (entries[i].lru_counter < min_lru) {
            min_lru = entries[i].lru_counter;
            victim_index = i;
        }
    }
    
    // Insertar nueva entrada
    entries[victim_index].process_id = process_id;
    entries[victim_index].vpn = vpn;
    entries[victim_index].frame = frame;
    entries[victim_index].valid = true;
    entries[victim_index].lru_counter = global_lru_counter++;
    
    pthread_mutex_unlock(&tlb_mutex);
}

void TLB::invalidate_process(int process_id) {
    pthread_mutex_lock(&tlb_mutex);
    
    for (int i = 0; i < TLB_SIZE; i++) {
        if (entries[i].valid && entries[i].process_id == process_id) {
            entries[i].valid = false;
        }
    }
    
    pthread_mutex_unlock(&tlb_mutex);
}

void TLB::invalidate_entry(int process_id, uint8_t vpn) {
    pthread_mutex_lock(&tlb_mutex);
    
    for (int i = 0; i < TLB_SIZE; i++) {
        if (entries[i].valid && 
            entries[i].process_id == process_id && 
            entries[i].vpn == vpn) {
            entries[i].valid = false;
        }
    }
    
    pthread_mutex_unlock(&tlb_mutex);
}

void TLB::get_statistics(int& hit_count, int& miss_count, double& hit_rate) {
    pthread_mutex_lock(&tlb_mutex);
    
    hit_count = hits;
    miss_count = misses;
    
    if ((hits + misses) > 0) {
        hit_rate = (double)hits / (hits + misses) * 100.0;
    } else {
        hit_rate = 0.0;
    }
    
    pthread_mutex_unlock(&tlb_mutex);
}

void TLB::reset_statistics() {
    pthread_mutex_lock(&tlb_mutex);
    hits = 0;
    misses = 0;
    pthread_mutex_unlock(&tlb_mutex);
}

void TLB::print_status() {
    pthread_mutex_lock(&tlb_mutex);
    
    std::cout << "\n=== Estado del TLB ===" << std::endl;
    int valid_entries = 0;
    for (int i = 0; i < TLB_SIZE; i++) {
        if (entries[i].valid) {
            valid_entries++;
        }
    }
    std::cout << "Entradas válidas: " << valid_entries << "/" << TLB_SIZE << std::endl;
    
    pthread_mutex_unlock(&tlb_mutex);
}


// IMPLEMENTACIÓN: PageTable


PageTable::PageTable(int pid) : process_id(pid) {
    pthread_mutex_init(&pt_mutex, nullptr);
    // Inicializar todas las entradas como inválidas
    for (int i = 0; i < NUM_PAGES; i++) {
        entries[i] = PageTableEntry();
    }
}

PageTable::~PageTable() {
    pthread_mutex_destroy(&pt_mutex);
}

PageTableEntry* PageTable::get_entry(uint8_t vpn) {
    if (vpn >= NUM_PAGES) {
        return nullptr;
    }
    return &entries[vpn];
}

void PageTable::update_entry(uint8_t vpn, uint8_t frame, bool valid, bool dirty, bool reference) {
    if (vpn >= NUM_PAGES) {
        return;
    }
    
    pthread_mutex_lock(&pt_mutex);
    entries[vpn].frame = frame;
    entries[vpn].valid = valid;
    entries[vpn].dirty = dirty;
    entries[vpn].reference = reference;
    pthread_mutex_unlock(&pt_mutex);
}

void PageTable::set_reference_bit(uint8_t vpn, bool value) {
    if (vpn >= NUM_PAGES) {
        return;
    }
    
    pthread_mutex_lock(&pt_mutex);
    entries[vpn].reference = value;
    pthread_mutex_unlock(&pt_mutex);
}

void PageTable::set_dirty_bit(uint8_t vpn, bool value) {
    if (vpn >= NUM_PAGES) {
        return;
    }
    
    pthread_mutex_lock(&pt_mutex);
    entries[vpn].dirty = value;
    pthread_mutex_unlock(&pt_mutex);
}

void PageTable::invalidate_page(uint8_t vpn) {
    if (vpn >= NUM_PAGES) {
        return;
    }
    
    pthread_mutex_lock(&pt_mutex);
    entries[vpn].valid = false;
    pthread_mutex_unlock(&pt_mutex);
}

std::vector<uint8_t> PageTable::get_valid_pages() {
    std::vector<uint8_t> valid_pages;
    
    pthread_mutex_lock(&pt_mutex);
    for (int i = 0; i < NUM_PAGES; i++) {
        if (entries[i].valid) {
            valid_pages.push_back(i);
        }
    }
    pthread_mutex_unlock(&pt_mutex);
    
    return valid_pages;
}
