#include "virtual_memory_system.h"
#include <iostream>
#include <iomanip>


CPU::CPU(int pid, MMU* memory_unit) 
    : pc(0), zero_flag(false), halt_flag(false), process_id(pid), mmu(memory_unit) {
    for (int i = 0; i < NUM_REGISTERS; i++) {
        registers[i] = 0;
    }
}

Instruction CPU::fetch(const std::vector<Instruction>& program) {
    if (pc >= program.size()) {
        Instruction halt_inst;
        halt_inst.type = INST_HALT;
        return halt_inst;
    }
    
    return program[pc];
}

void CPU::execute(const Instruction& inst, std::map<std::string, int>& labels) {
    switch (inst.type) {
        case INST_MOV:
            if (inst.operand3 == 1) {
                registers[inst.operand1] = registers[inst.operand2];
            } else {
                registers[inst.operand1] = inst.operand2;
            }
            pc++;
            break;
            
        case INST_LOAD:
            if (inst.is_memory_address) {
                registers[inst.operand1] = read_memory(inst.operand2);
            } else {
                registers[inst.operand1] = inst.operand2;
            }
            pc++;
            break;
            
        case INST_STORE:
            write_memory(inst.operand1, registers[inst.operand2]);
            pc++;
            break;
            
        case INST_ADD:
            registers[inst.operand1] = registers[inst.operand2] + registers[inst.operand3];
            pc++;
            break;
            
        case INST_SUB:
            registers[inst.operand1] = registers[inst.operand2] - registers[inst.operand3];
            pc++;
            break;
            
        case INST_MUL:
            registers[inst.operand1] = registers[inst.operand2] * registers[inst.operand3];
            pc++;
            break;
            
        case INST_DIV:
            if (registers[inst.operand3] != 0) {
                registers[inst.operand1] = registers[inst.operand2] / registers[inst.operand3];
            } else {
                pthread_mutex_lock(&print_mutex);
                std::cerr << "Error: división por cero en Proceso " << process_id << std::endl;
                pthread_mutex_unlock(&print_mutex);
                registers[inst.operand1] = 0;
            }
            pc++;
            break;
            
        case INST_INC:
            registers[inst.operand1]++;
            pc++;
            break;
            
        case INST_DEC:
            registers[inst.operand1]--;
            pc++;
            break;
            
        case INST_CMP:
            zero_flag = (registers[inst.operand1] == registers[inst.operand2]);
            pc++;
            break;
            
        case INST_JMP:
            if (labels.find(inst.label) != labels.end()) {
                pc = labels[inst.label];
            } else {
                pthread_mutex_lock(&print_mutex);
                std::cerr << "Error: etiqueta no encontrada: " << inst.label << std::endl;
                pthread_mutex_unlock(&print_mutex);
                pc++;
            }
            break;
            
        case INST_JE:
            if (zero_flag && labels.find(inst.label) != labels.end()) {
                pc = labels[inst.label];
            } else {
                pc++;
            }
            break;
            
        case INST_JNE:
            if (!zero_flag && labels.find(inst.label) != labels.end()) {
                pc = labels[inst.label];
            } else {
                pc++;
            }
            break;
            
        case INST_HALT:
            halt_flag = true;
            break;
    }
}

int CPU::read_memory(uint16_t address) {
    uint16_t physical_address = mmu->translate(process_id, address, false);
    
    DataCache* cache = mmu->get_data_cache();
    PhysicalMemory* phys_mem = mmu->get_physical_memory();
    
    uint16_t block_address = (physical_address / CACHE_BLOCK_SIZE) * CACHE_BLOCK_SIZE;
    uint8_t cached_data[CACHE_BLOCK_SIZE];
    
    if (cache->lookup(block_address, cached_data)) {
        int offset = physical_address % CACHE_BLOCK_SIZE;
        int value = 0;
        for (int i = 0; i < 4 && (offset + i) < CACHE_BLOCK_SIZE; i++) {
            value |= (cached_data[offset + i] << (i * 8));
        }
        return value;
    }
    
    uint8_t block_data[CACHE_BLOCK_SIZE];
    for (int i = 0; i < CACHE_BLOCK_SIZE; i++) {
        block_data[i] = phys_mem->read_byte(block_address + i);
    }
    
    cache->insert(block_address, block_data);
    
    int value = 0;
    for (int i = 0; i < 4; i++) {
        uint8_t byte = phys_mem->read_byte(physical_address + i);
        value |= (byte << (i * 8));
    }
    
    return value;
}

void CPU::write_memory(uint16_t address, int value) {
    uint16_t physical_address = mmu->translate(process_id, address, true);
    
    PhysicalMemory* phys_mem = mmu->get_physical_memory();
    DataCache* cache = mmu->get_data_cache();
    
    for (int i = 0; i < 4; i++) {
        uint8_t byte = (value >> (i * 8)) & 0xFF;
        phys_mem->write_byte(physical_address + i, byte);
    }
    
    uint16_t block_address = (physical_address / CACHE_BLOCK_SIZE) * CACHE_BLOCK_SIZE;
    uint8_t block_data[CACHE_BLOCK_SIZE];
    for (int i = 0; i < CACHE_BLOCK_SIZE; i++) {
        block_data[i] = phys_mem->read_byte(block_address + i);
    }
    cache->insert(block_address, block_data);
}

void CPU::print_registers() {
    pthread_mutex_lock(&print_mutex);
    std::cout << "\nProceso " << process_id << " - Registros finales:" << std::endl;
    for (int i = 0; i < NUM_REGISTERS; i++) {
        std::cout << "  R" << i << "=" << registers[i];
        if (i % 5 == 4) std::cout << std::endl;
    }
    std::cout << std::endl;
    pthread_mutex_unlock(&print_mutex);
}
