#ifndef VIRTUAL_MEMORY_SYSTEM_H
#define VIRTUAL_MEMORY_SYSTEM_H

#include <cstdint>
#include <cstring>
#include <vector>
#include <map>
#include <string>
#include <pthread.h>
#include <queue>


// CONSTANTES DEL SISTEMA

const int PHYSICAL_MEMORY_SIZE = 512;      // 512 bytes de RAM
const int FRAME_SIZE = 16;                  // 16 bytes por frame
const int NUM_FRAMES = 32;                  // 32 frames en memoria física
const int PAGE_SIZE = 16;                   // 16 bytes por página
const int NUM_PAGES = 64;                   // 64 páginas por proceso
const int VIRTUAL_MEMORY_SIZE = 1024;       // 1 KB de memoria virtual por proceso
const int MAX_PROCESSES = 4;                // Máximo 4 procesos concurrentes
const int TLB_SIZE = 4;                     // 4 entradas en TLB
const int NUM_REGISTERS = 10;               // Registros R0-R9
const int DATA_CACHE_SIZE = 8;              // 8 entradas en caché de datos
const int CACHE_BLOCK_SIZE = 4;             // 4 bytes por bloque de caché

// Mutex global para sincronizar salida
extern pthread_mutex_t print_mutex;

// Bits de direccionamiento
const int OFFSET_BITS = 4;                  // 4 bits para offset (16 bytes)
const int VPN_BITS = 6;                     // 6 bits para VPN (64 páginas)
const int FRAME_BITS = 5;                   // 5 bits para frame (32 frames)

// Máscaras para extracción de bits
const uint16_t OFFSET_MASK = 0x0F;          // 0000 0000 0000 1111
const uint16_t VPN_MASK = 0x3F0;            // 0000 0011 1111 0000


// ESTRUCTURAS DE DATOS


// Entrada de la tabla de páginas (PTE)
struct PageTableEntry {
    bool valid;          // V bit - página en memoria
    bool dirty;          // D bit - página modificada
    bool reference;      // R bit - acceso reciente
    uint8_t frame;       // Número de frame (0-31)
    
    PageTableEntry() : valid(false), dirty(false), reference(false), frame(0) {}
};

// Entrada del TLB
struct TLBEntry {
    int process_id;      // ID del proceso
    uint8_t vpn;         // Número de página virtual
    uint8_t frame;       // Número de frame
    bool valid;          // Entrada válida
    uint32_t lru_counter; // Contador LRU
    
    TLBEntry() : process_id(-1), vpn(0), frame(0), valid(false), lru_counter(0) {}
};

// Entrada de caché de datos
struct DataCacheEntry {
    uint16_t tag;               // Tag de dirección física
    uint8_t data[CACHE_BLOCK_SIZE]; // Bloque de datos
    bool valid;                 // Entrada válida
    uint32_t lru_counter;       // Contador LRU
    
    DataCacheEntry() : tag(0), valid(false), lru_counter(0) {
        memset(data, 0, CACHE_BLOCK_SIZE);
    }
};

// Información de un frame en memoria física
struct FrameInfo {
    bool is_free;        // Frame libre
    int process_id;      // ID del proceso que lo usa
    uint8_t vpn;         // Página virtual que contiene
    
    FrameInfo() : is_free(true), process_id(-1), vpn(0) {}
};

// Tipos de instrucciones
enum InstructionType {
    INST_MOV,   // MOV R1, 5
    INST_LOAD,  // LD R1, [addr]
    INST_STORE, // ST [addr], R1
    INST_ADD,   // ADD R3, R1, R2
    INST_SUB,   // SUB R3, R1, R2
    INST_MUL,   // MUL R3, R1, R2
    INST_DIV,   // DIV R3, R1, R2
    INST_INC,   // INC R1
    INST_DEC,   // DEC R1
    INST_CMP,   // CMP R1, R2
    INST_JMP,   // JMP label
    INST_JE,    // JE label (Jump if Equal)
    INST_JNE,   // JNE label (Jump if Not Equal)
    INST_HALT   // HALT
};

// Estructura de una instrucción
struct Instruction {
    InstructionType type;
    int operand1;        // Registro o valor
    int operand2;        // Registro o valor
    int operand3;        // Registro (para operaciones de 3 operandos)
    std::string label;   // Para JMP
    bool is_memory_address; // Para LOAD/STORE
    
    Instruction() : type(INST_HALT), operand1(0), operand2(0), operand3(0), 
                    label(""), is_memory_address(false) {}
};


// CLASES FORWARD DECLARATION

class PhysicalMemory;
class EnhancedSecondChance;
class LRUReplacement;
class DataCache;
class TLB;
class PageTable;
class MMU;
class CPU;
class Process;
class VirtualMemorySystem;


// CLASE: TLB (Translation Lookaside Buffer)

class TLB {
private:
    TLBEntry entries[TLB_SIZE];
    uint32_t global_lru_counter;
    pthread_mutex_t tlb_mutex;
    
    // Estadísticas
    int hits;
    int misses;
    
public:
    TLB();
    ~TLB();
    
    // Buscar entrada en TLB
    bool lookup(int process_id, uint8_t vpn, uint8_t& frame);
    
    // Insertar entrada en TLB
    void insert(int process_id, uint8_t vpn, uint8_t frame);
    
    // Invalidar entradas de un proceso
    void invalidate_process(int process_id);
    
    // Invalidar entrada específica
    void invalidate_entry(int process_id, uint8_t vpn);
    
    // Obtener estadísticas
    void get_statistics(int& hit_count, int& miss_count, double& hit_rate);
    
    // Resetear estadísticas
    void reset_statistics();
    
    // Imprimir estado del TLB
    void print_status();
};


// CLASE: DataCache (Caché de Datos)

class DataCache {
private:
    DataCacheEntry entries[DATA_CACHE_SIZE];
    uint32_t global_lru_counter;
    pthread_mutex_t cache_mutex;
    
    int hits;
    int misses;
    
    int find_lru_entry();
    
public:
    DataCache();
    ~DataCache();
    
    bool lookup(uint16_t physical_address, uint8_t* data);
    void insert(uint16_t physical_address, const uint8_t* data);
    void invalidate();
    
    void get_statistics(int& hit_count, int& miss_count, double& hit_rate);
    void reset_statistics();
    void print_status();
};


// CLASE: PageTable (Tabla de Páginas)

class PageTable {
private:
    PageTableEntry entries[NUM_PAGES];
    int process_id;
    pthread_mutex_t pt_mutex;
    
public:
    PageTable(int pid);
    ~PageTable();
    
    // Obtener entrada de la tabla de páginas
    PageTableEntry* get_entry(uint8_t vpn);
    
    // Actualizar entrada
    void update_entry(uint8_t vpn, uint8_t frame, bool valid, bool dirty, bool reference);
    
    // Marcar página como referenciada
    void set_reference_bit(uint8_t vpn, bool value);
    
    // Marcar página como sucia
    void set_dirty_bit(uint8_t vpn, bool value);
    
    // Invalidar página
    void invalidate_page(uint8_t vpn);
    
    // Obtener todas las páginas válidas
    std::vector<uint8_t> get_valid_pages();
    
    int get_process_id() const { return process_id; }
};


// CLASE: EnhancedSecondChance (Algoritmo de Reemplazo)

class EnhancedSecondChance {
private:
    int clock_hand;
    PhysicalMemory* physical_memory;
    std::map<int, PageTable*> page_tables;
    
    // Clasificar página según bits R y D
    int classify_page(bool reference, bool dirty);
    
public:
    EnhancedSecondChance(PhysicalMemory* mem);
    
    // Registrar tabla de páginas
    void register_page_table(int process_id, PageTable* pt);
    
    // Seleccionar víctima para reemplazo
    int select_victim();
    
    // Obtener información de la página víctima
    void get_victim_info(int frame, int& pid, uint8_t& vpn, bool& is_dirty);
};


// CLASE: LRUReplacement (Algoritmo de Reemplazo LRU)

class LRUReplacement {
private:
    PhysicalMemory* physical_memory;
    std::map<int, PageTable*> page_tables;
    std::map<int, uint32_t> frame_access_time;
    uint32_t global_time;
    pthread_mutex_t lru_mutex;
    
public:
    LRUReplacement(PhysicalMemory* mem);
    ~LRUReplacement();
    
    void register_page_table(int process_id, PageTable* pt);
    void update_access_time(int frame);
    int select_victim();
    void get_victim_info(int frame, int& pid, uint8_t& vpn, bool& is_dirty);
};


// CLASE: PhysicalMemory (Memoria Física)

class PhysicalMemory {
private:
    uint8_t memory[PHYSICAL_MEMORY_SIZE];
    FrameInfo frames[NUM_FRAMES];
    EnhancedSecondChance* esc_algorithm;
    LRUReplacement* lru_algorithm;
    bool use_lru;
    pthread_mutex_t memory_mutex;
    
    int free_frame_count;
    
public:
    PhysicalMemory();
    ~PhysicalMemory();
    
    void set_replacement_algorithm(EnhancedSecondChance* esc, LRUReplacement* lru, bool use_lru_mode);
    
    int get_free_frame();
    int allocate_frame(int process_id, uint8_t vpn);
    void free_frame(int frame_num);
    
    uint8_t read_byte(uint16_t physical_address);
    void write_byte(uint16_t physical_address, uint8_t value);
    
    void load_page_from_disk(int frame_num, int process_id, uint8_t vpn, const std::string& program_file);
    void write_page_to_disk(int frame_num, int process_id, uint8_t vpn);
    
    FrameInfo* get_frame_info(int frame_num);
    std::vector<int> get_process_frames(int process_id);
    
    void print_memory_status();
};


// CLASE: MMU (Memory Management Unit)

class MMU {
private:
    TLB* tlb;
    DataCache* data_cache;
    std::map<int, PageTable*> page_tables;
    std::map<int, std::string> program_files;
    PhysicalMemory* physical_memory;
    pthread_mutex_t mmu_mutex;
    
    int page_faults;
    int total_accesses;
    
public:
    MMU(PhysicalMemory* mem);
    ~MMU();
    
    void register_page_table(int process_id, PageTable* pt, const std::string& program_file);
    void handle_page_fault(int process_id, uint8_t vpn);
    uint16_t translate(int process_id, uint16_t logical_address, bool is_write);
    
    void get_statistics(int& pf, int& accesses, double& pf_rate);
    
    TLB* get_tlb() { return tlb; }
    DataCache* get_data_cache() { return data_cache; }
    PhysicalMemory* get_physical_memory() { return physical_memory; }
};


// CLASE: CPU (Unidad de Procesamiento)

class CPU {
private:
    int registers[NUM_REGISTERS]; // R0-R9
    uint16_t pc;                  // Program Counter
    bool zero_flag;               // Flag de comparación
    bool halt_flag;               // Flag de detención
    
    int process_id;
    MMU* mmu;
    
public:
    CPU(int pid, MMU* memory_unit);
    
    // Fetch: obtener instrucción
    Instruction fetch(const std::vector<Instruction>& program);
    
    // Decode & Execute: decodificar y ejecutar
    void execute(const Instruction& inst, std::map<std::string, int>& labels);
    
    // Leer valor de memoria (32 bits / 4 bytes)
    int read_memory(uint16_t address);
    
    // Escribir valor en memoria (32 bits / 4 bytes)
    void write_memory(uint16_t address, int value);
    
    // Obtener/establecer registros
    int get_register(int reg) const { return registers[reg]; }
    void set_register(int reg, int value) { registers[reg] = value; }
    
    // Control del PC
    uint16_t get_pc() const { return pc; }
    void set_pc(uint16_t new_pc) { pc = new_pc; }
    void increment_pc() { pc++; }
    
    // Flags
    bool is_halted() const { return halt_flag; }
    void set_halt(bool value) { halt_flag = value; }
    bool get_zero_flag() const { return zero_flag; }
    
    // Imprimir estado de registros
    void print_registers();
};


// CLASE: Process (Proceso)

class Process {
private:
    int pid;
    PageTable* page_table;
    CPU* cpu;
    std::vector<Instruction> program;
    std::map<std::string, int> labels; // Para JMP
    std::string program_file;
    
    bool finished;
    
    // Estadísticas del proceso
    int instruction_count;
    int memory_accesses;
    
public:
    Process(int process_id, MMU* mmu, const std::string& prog_file);
    ~Process();
    
    // Cargar programa desde archivo
    bool load_program();
    
    // Ejecutar proceso
    void run();
    
    // Getters
    int get_pid() const { return pid; }
    PageTable* get_page_table() { return page_table; }
    bool is_finished() const { return finished; }
    int get_instruction_count() const { return instruction_count; }
    int get_memory_accesses() const { return memory_accesses; }
    
    // Para uso con fork
    void execute_instructions();
};


// CLASE: VirtualMemorySystem (Sistema Principal)

class VirtualMemorySystem {
private:
    PhysicalMemory* physical_memory;
    MMU* mmu;
    EnhancedSecondChance* esc_algorithm;
    LRUReplacement* lru_algorithm;
    
    std::vector<Process*> processes;
    std::vector<pthread_t> thread_ids;
    
    int next_process_id;
    bool use_lru;
    
    static void* thread_runner(void* arg);
    
public:
    VirtualMemorySystem(bool use_lru_mode = false);
    ~VirtualMemorySystem();
    
    bool create_process(const std::string& program_file);
    void run_all_processes();
    void wait_all_processes();
    void print_statistics();
    void cleanup();
};

#endif // VIRTUAL_MEMORY_SYSTEM_H