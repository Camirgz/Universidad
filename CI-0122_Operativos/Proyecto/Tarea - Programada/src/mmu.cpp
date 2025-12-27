#include "virtual_memory_system.h"
#include <iostream>
#include <iomanip>


// IMPLEMENTACIÓN: MMU


MMU::MMU(PhysicalMemory* mem) 
    : physical_memory(mem), page_faults(0), total_accesses(0) {
    pthread_mutex_init(&mmu_mutex, nullptr);
    tlb = new TLB();
    data_cache = new DataCache();
}

MMU::~MMU() {
    delete tlb;
    delete data_cache;
    pthread_mutex_destroy(&mmu_mutex);
}

void MMU::register_page_table(int process_id, PageTable* pt, const std::string& program_file) {
    pthread_mutex_lock(&mmu_mutex);
    page_tables[process_id] = pt;
    program_files[process_id] = program_file;
    pthread_mutex_unlock(&mmu_mutex);
}

void MMU::handle_page_fault(int process_id, uint8_t vpn) {
    pthread_mutex_lock(&mmu_mutex);
    page_faults++;
    pthread_mutex_unlock(&mmu_mutex);
    
    int frame = physical_memory->allocate_frame(process_id, vpn);
    
    if (frame == -1) {
        pthread_mutex_lock(&print_mutex);
        std::cerr << "Error: no se pudo alocar frame" << std::endl;
        pthread_mutex_unlock(&print_mutex);
        return;
    }
    
    pthread_mutex_lock(&mmu_mutex);
    std::string prog_file = program_files[process_id];
    pthread_mutex_unlock(&mmu_mutex);
    
    physical_memory->load_page_from_disk(frame, process_id, vpn, prog_file);
    
    pthread_mutex_lock(&mmu_mutex);
    
    if (page_tables.find(process_id) != page_tables.end()) {
        PageTable* pt = page_tables[process_id];
        pt->update_entry(vpn, frame, true, false, true);
        tlb->insert(process_id, vpn, frame);
    }
    
    pthread_mutex_unlock(&mmu_mutex);
}

uint16_t MMU::translate(int process_id, uint16_t logical_address, bool is_write) {
    pthread_mutex_lock(&mmu_mutex);
    total_accesses++;
    pthread_mutex_unlock(&mmu_mutex);
    
    uint8_t vpn = (logical_address & VPN_MASK) >> OFFSET_BITS;
    uint8_t offset = logical_address & OFFSET_MASK;
    
    uint8_t frame;
    bool tlb_hit = tlb->lookup(process_id, vpn, frame);
    
    if (tlb_hit) {
        pthread_mutex_lock(&mmu_mutex);
        if (page_tables.find(process_id) != page_tables.end()) {
            PageTable* pt = page_tables[process_id];
            pt->set_reference_bit(vpn, true);
            
            if (is_write) {
                pt->set_dirty_bit(vpn, true);
            }
        }
        pthread_mutex_unlock(&mmu_mutex);
    } else {
        pthread_mutex_lock(&mmu_mutex);
        
        if (page_tables.find(process_id) == page_tables.end()) {
            pthread_mutex_unlock(&mmu_mutex);
            pthread_mutex_lock(&print_mutex);
            std::cerr << "Error: tabla de páginas no encontrada" << std::endl;
            pthread_mutex_unlock(&print_mutex);
            return 0;
        }
        
        PageTable* pt = page_tables[process_id];
        PageTableEntry* pte = pt->get_entry(vpn);
        
        if (pte == nullptr) {
            pthread_mutex_unlock(&mmu_mutex);
            pthread_mutex_lock(&print_mutex);
            std::cerr << "Error: VPN inválido" << std::endl;
            pthread_mutex_unlock(&print_mutex);
            return 0;
        }
        
        bool page_valid = pte->valid;
        
        pthread_mutex_unlock(&mmu_mutex);
        
        if (!page_valid) {
            handle_page_fault(process_id, vpn);
            
            pthread_mutex_lock(&mmu_mutex);
            pte = pt->get_entry(vpn);
            pthread_mutex_unlock(&mmu_mutex);
        } else {
            pthread_mutex_lock(&mmu_mutex);
            frame = pte->frame;
            pthread_mutex_unlock(&mmu_mutex);
            
            tlb->insert(process_id, vpn, frame);
        }
        
        pthread_mutex_lock(&mmu_mutex);
        
        frame = pte->frame;
        
        pt->set_reference_bit(vpn, true);
        if (is_write) {
            pt->set_dirty_bit(vpn, true);
        }
        
        pthread_mutex_unlock(&mmu_mutex);
    }
    
    uint16_t physical_address = (frame << OFFSET_BITS) | offset;
    
    return physical_address;
}

void MMU::get_statistics(int& pf, int& accesses, double& pf_rate) {
    pthread_mutex_lock(&mmu_mutex);
    
    pf = page_faults;
    accesses = total_accesses;
    
    if (total_accesses > 0) {
        pf_rate = (double)page_faults / total_accesses * 100.0;
    } else {
        pf_rate = 0.0;
    }
    
    pthread_mutex_unlock(&mmu_mutex);
}