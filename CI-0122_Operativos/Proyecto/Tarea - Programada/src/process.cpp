#include "virtual_memory_system.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


// IMPLEMENTACIÓN: Process


Process::Process(int process_id, MMU* mmu, const std::string& prog_file)
    : pid(process_id), program_file(prog_file), finished(false) {
    page_table = new PageTable(process_id);
    cpu = new CPU(process_id, mmu);
    
    mmu->register_page_table(process_id, page_table, prog_file);
}

Process::~Process() {
    delete cpu;
    delete page_table;
}

bool Process::load_program() {
    std::ifstream file(program_file);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open program file: " << program_file << std::endl;
        return false;
    }
    
    std::string line;
    
    while (std::getline(file, line)) {
        // Eliminar espacios al inicio y final
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        
        // Ignorar líneas vacías y comentarios
        if (line.empty() || line[0] == ';' || line[0] == '#') {
            continue;
        }
        
        // Verificar si es una etiqueta
        size_t colon_pos = line.find(':');
        if (colon_pos != std::string::npos && colon_pos < line.find(' ')) {
            std::string label = line.substr(0, colon_pos);
            labels[label] = program.size();
            
            // Procesar el resto de la línea si hay algo después de ':'
            line = line.substr(colon_pos + 1);
            line.erase(0, line.find_first_not_of(" \t"));
            if (line.empty()) {
                continue;
            }
        }
        
        // Parsear instrucción
        std::istringstream iss(line);
        std::string opcode;
        iss >> opcode;
        
        std::transform(opcode.begin(), opcode.end(), opcode.begin(), ::toupper);
        
        Instruction inst;
        
        try {
            if (opcode == "MOV") {
                inst.type = INST_MOV;
                std::string reg, value;
                iss >> reg >> value;
                reg.erase(remove(reg.begin(), reg.end(), ','), reg.end());
                
                if (reg.length() < 2 || (reg[0] != 'R' && reg[0] != 'r')) {
                    continue;
                }
                int reg_num = std::stoi(reg.substr(1));
                if (reg_num < 0 || reg_num >= NUM_REGISTERS) {
                    continue;
                }
                inst.operand1 = reg_num;
                
                if (value.length() > 1 && (value[0] == 'R' || value[0] == 'r')) {
                    int src_reg = std::stoi(value.substr(1));
                    if (src_reg < 0 || src_reg >= NUM_REGISTERS) {
                        continue;
                    }
                    inst.operand2 = src_reg;
                    inst.operand3 = 1;
                } else {
                    inst.operand2 = std::stoi(value);
                    inst.operand3 = 0;
                }
                
            } else if (opcode == "LD" || opcode == "LOAD") {
                inst.type = INST_LOAD;
                std::string reg, addr;
                iss >> reg >> addr;
                reg.erase(remove(reg.begin(), reg.end(), ','), reg.end());
                
                if (reg.length() < 2 || (reg[0] != 'R' && reg[0] != 'r')) {
                    continue;
                }
                int reg_num = std::stoi(reg.substr(1));
                if (reg_num < 0 || reg_num >= NUM_REGISTERS) {
                    continue;
                }
                inst.operand1 = reg_num;
                
                if (addr[0] == '[') {
                    inst.is_memory_address = true;
                    addr.erase(remove(addr.begin(), addr.end(), '['), addr.end());
                    addr.erase(remove(addr.begin(), addr.end(), ']'), addr.end());
                }
                int address = std::stoi(addr);
                if (address < 0 || address >= VIRTUAL_MEMORY_SIZE) {
                    continue;
                }
                inst.operand2 = address;
                
            } else if (opcode == "ST" || opcode == "STORE") {
                inst.type = INST_STORE;
                std::string addr, reg;
                iss >> addr >> reg;
                addr.erase(remove(addr.begin(), addr.end(), ','), addr.end());
                addr.erase(remove(addr.begin(), addr.end(), '['), addr.end());
                addr.erase(remove(addr.begin(), addr.end(), ']'), addr.end());
                
                int address = std::stoi(addr);
                if (address < 0 || address >= VIRTUAL_MEMORY_SIZE) {
                    continue;
                }
                inst.operand1 = address;
                
                if (reg.length() < 2 || (reg[0] != 'R' && reg[0] != 'r')) {
                    continue;
                }
                int reg_num = std::stoi(reg.substr(1));
                if (reg_num < 0 || reg_num >= NUM_REGISTERS) {
                    continue;
                }
                inst.operand2 = reg_num;
                
            } else if (opcode == "ADD" || opcode == "SUB" || opcode == "MUL" || opcode == "DIV") {
                if (opcode == "ADD") inst.type = INST_ADD;
                else if (opcode == "SUB") inst.type = INST_SUB;
                else if (opcode == "MUL") inst.type = INST_MUL;
                else inst.type = INST_DIV;
                
                std::string rd, rs1, rs2;
                iss >> rd >> rs1 >> rs2;
                rd.erase(remove(rd.begin(), rd.end(), ','), rd.end());
                rs1.erase(remove(rs1.begin(), rs1.end(), ','), rs1.end());
                
                if (rd.length() < 2 || rs1.length() < 2 || rs2.length() < 2) {
                    continue;
                }
                
                int rd_num = std::stoi(rd.substr(1));
                int rs1_num = std::stoi(rs1.substr(1));
                int rs2_num = std::stoi(rs2.substr(1));
                
                if (rd_num < 0 || rd_num >= NUM_REGISTERS ||
                    rs1_num < 0 || rs1_num >= NUM_REGISTERS ||
                    rs2_num < 0 || rs2_num >= NUM_REGISTERS) {
                    continue;
                }
                
                inst.operand1 = rd_num;
                inst.operand2 = rs1_num;
                inst.operand3 = rs2_num;
                
            } else if (opcode == "INC" || opcode == "DEC") {
                inst.type = (opcode == "INC") ? INST_INC : INST_DEC;
                std::string reg;
                iss >> reg;
                
                if (reg.length() < 2 || (reg[0] != 'R' && reg[0] != 'r')) {
                    continue;
                }
                int reg_num = std::stoi(reg.substr(1));
                if (reg_num < 0 || reg_num >= NUM_REGISTERS) {
                    continue;
                }
                inst.operand1 = reg_num;
                
            } else if (opcode == "CMP") {
                inst.type = INST_CMP;
                std::string r1, r2;
                iss >> r1 >> r2;
                r1.erase(remove(r1.begin(), r1.end(), ','), r1.end());
                
                if (r1.length() < 2 || r2.length() < 2) {
                    continue;
                }
                
                int r1_num = std::stoi(r1.substr(1));
                int r2_num = std::stoi(r2.substr(1));
                
                if (r1_num < 0 || r1_num >= NUM_REGISTERS ||
                    r2_num < 0 || r2_num >= NUM_REGISTERS) {
                    continue;
                }
                
                inst.operand1 = r1_num;
                inst.operand2 = r2_num;
                
            } else if (opcode == "JMP" || opcode == "JE" || opcode == "JNE") {
                if (opcode == "JMP") inst.type = INST_JMP;
                else if (opcode == "JE") inst.type = INST_JE;
                else inst.type = INST_JNE;
                iss >> inst.label;
                
            } else if (opcode == "HALT") {
                inst.type = INST_HALT;
                
            } else {
                continue;
            }
            
            program.push_back(inst);
            
        } catch (const std::exception& e) {
            continue;
        }
    }
    
    file.close();
    
    pthread_mutex_lock(&print_mutex);
    std::cout << "Proceso " << pid << " cargó " << program.size() 
              << " instrucciones" << std::endl;
    pthread_mutex_unlock(&print_mutex);
    
    return !program.empty();
}

void Process::execute_instructions() {
    pthread_mutex_lock(&print_mutex);
    std::cout << "\nProceso " << pid << " iniciado" << std::endl;
    pthread_mutex_unlock(&print_mutex);
    
    int instruction_count = 0;
    const int MAX_INSTRUCTIONS = 1000;
    
    while (!cpu->is_halted() && instruction_count < MAX_INSTRUCTIONS) {
        Instruction inst = cpu->fetch(program);
        cpu->execute(inst, labels);
        instruction_count++;
    }
    
    pthread_mutex_lock(&print_mutex);
    if (instruction_count >= MAX_INSTRUCTIONS) {
        std::cout << "Proceso " << pid << " terminado: límite de instrucciones alcanzado" << std::endl;
    } else {
        std::cout << "Proceso " << pid << " finalizado (" 
                  << instruction_count << " instrucciones)" << std::endl;
    }
    pthread_mutex_unlock(&print_mutex);
    
    cpu->print_registers();
    
    finished = true;
}

void Process::run() {
    execute_instructions();
}
