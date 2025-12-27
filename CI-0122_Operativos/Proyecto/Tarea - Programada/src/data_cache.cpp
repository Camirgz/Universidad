#include "virtual_memory_system.h"
#include <iostream>
#include <iomanip>


// IMPLEMENTACIÓN: DataCache


DataCache::DataCache() : global_lru_counter(0), hits(0), misses(0) {
    pthread_mutex_init(&cache_mutex, nullptr);
    
    for (int i = 0; i < DATA_CACHE_SIZE; i++) {
        entries[i] = DataCacheEntry();
    }
}

DataCache::~DataCache() {
    pthread_mutex_destroy(&cache_mutex);
}

int DataCache::find_lru_entry() {
    int lru_index = 0;
    uint32_t min_counter = entries[0].lru_counter;
    
    for (int i = 1; i < DATA_CACHE_SIZE; i++) {
        if (!entries[i].valid) {
            return i;
        }
        if (entries[i].lru_counter < min_counter) {
            min_counter = entries[i].lru_counter;
            lru_index = i;
        }
    }
    
    return lru_index;
}

bool DataCache::lookup(uint16_t physical_address, uint8_t* data) {
    pthread_mutex_lock(&cache_mutex);
    
    uint16_t block_address = (physical_address / CACHE_BLOCK_SIZE) * CACHE_BLOCK_SIZE;
    uint16_t tag = block_address;
    
    for (int i = 0; i < DATA_CACHE_SIZE; i++) {
        if (entries[i].valid && entries[i].tag == tag) {
            for (int j = 0; j < CACHE_BLOCK_SIZE; j++) {
                data[j] = entries[i].data[j];
            }
            entries[i].lru_counter = global_lru_counter++;
            hits++;
            pthread_mutex_unlock(&cache_mutex);
            return true;
        }
    }
    
    misses++;
    pthread_mutex_unlock(&cache_mutex);
    return false;
}

void DataCache::insert(uint16_t physical_address, const uint8_t* data) {
    pthread_mutex_lock(&cache_mutex);
    
    uint16_t block_address = (physical_address / CACHE_BLOCK_SIZE) * CACHE_BLOCK_SIZE;
    uint16_t tag = block_address;
    
    int index = find_lru_entry();
    
    entries[index].tag = tag;
    entries[index].valid = true;
    for (int i = 0; i < CACHE_BLOCK_SIZE; i++) {
        entries[index].data[i] = data[i];
    }
    entries[index].lru_counter = global_lru_counter++;
    
    pthread_mutex_unlock(&cache_mutex);
}

void DataCache::invalidate() {
    pthread_mutex_lock(&cache_mutex);
    
    for (int i = 0; i < DATA_CACHE_SIZE; i++) {
        entries[i].valid = false;
    }
    
    pthread_mutex_unlock(&cache_mutex);
}

void DataCache::get_statistics(int& hit_count, int& miss_count, double& hit_rate) {
    pthread_mutex_lock(&cache_mutex);
    
    hit_count = hits;
    miss_count = misses;
    
    int total = hits + misses;
    if (total > 0) {
        hit_rate = (double)hits / total * 100.0;
    } else {
        hit_rate = 0.0;
    }
    
    pthread_mutex_unlock(&cache_mutex);
}

void DataCache::reset_statistics() {
    pthread_mutex_lock(&cache_mutex);
    hits = 0;
    misses = 0;
    pthread_mutex_unlock(&cache_mutex);
}

void DataCache::print_status() {
    pthread_mutex_lock(&cache_mutex);
    
    std::cout << "\n=== Estado de Caché de Datos ===" << std::endl;
    std::cout << "Entrada | Válida | Tag     | LRU" << std::endl;
    std::cout << "--------+--------+---------+----" << std::endl;
    
    for (int i = 0; i < DATA_CACHE_SIZE; i++) {
        std::cout << std::setw(7) << i << " | ";
        std::cout << std::setw(6) << (entries[i].valid ? "Sí" : "No") << " | ";
        if (entries[i].valid) {
            std::cout << "0x" << std::hex << std::setw(4) << std::setfill('0') 
                     << entries[i].tag << std::dec << std::setfill(' ') << " | ";
            std::cout << std::setw(3) << entries[i].lru_counter;
        } else {
            std::cout << "   -    | -";
        }
        std::cout << std::endl;
    }
    
    int total = hits + misses;
    double hit_rate = total > 0 ? (double)hits / total * 100.0 : 0.0;
    
    std::cout << "\nHits: " << hits << " | Misses: " << misses 
             << " | Hit Rate: " << std::fixed << std::setprecision(2) 
             << hit_rate << "%" << std::endl;
    
    pthread_mutex_unlock(&cache_mutex);
}
