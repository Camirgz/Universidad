#include "Pasteleria.h"
#include <iostream>
#include <unistd.h>

using namespace std;

Pasteleria::Pasteleria() {
    // Inicializar semáforo con 2 hornos disponibles
    sem_init(&hornos_disponibles, 0, NUM_HORNOS);
    
    // Inicializar mutex
    pthread_mutex_init(&mutex_colas, NULL);
    pthread_mutex_init(&mutex_hornos, NULL);
    pthread_mutex_init(&mutex_cout, NULL);
    
    // Inicializar estado de hornos
    for (int i = 0; i < NUM_HORNOS; i++) {
        horno_ocupado[i] = false;
    }
}

Pasteleria::~Pasteleria() {
    // Destruir semáforo y mutex
    sem_destroy(&hornos_disponibles);
    pthread_mutex_destroy(&mutex_colas);
    pthread_mutex_destroy(&mutex_hornos);
    pthread_mutex_destroy(&mutex_cout);
}

void Pasteleria::imprimir(const string& mensaje) {
    pthread_mutex_lock(&mutex_cout);
    cout << mensaje << endl;
    pthread_mutex_unlock(&mutex_cout);
}

int Pasteleria::asignar_horno() {
    // PRE: mutex_hornos debe estar bloqueado
    for (int i = 0; i < NUM_HORNOS; i++) {
        if (!horno_ocupado[i]) {
            horno_ocupado[i] = true;
            return i;
        }
    }
    return -1;
}

void Pasteleria::liberar_horno(int num_horno) {
    // PRE: mutex_hornos debe estar bloqueado
    horno_ocupado[num_horno] = false;
}

Platillo Pasteleria::obtener_siguiente_platillo() {
    // PRE: mutex_colas debe estar bloqueado
    Platillo platillo;
    
    // Prioridad a platillos urgentes
    if (!cola_urgente.empty()) {
        platillo = cola_urgente.front();
        cola_urgente.pop();
    } else {
        platillo = cola_normal.front();
        cola_normal.pop();
    }
    
    return platillo;
}

bool Pasteleria::hay_platillos_esperando() {
    // PRE: mutex_colas debe estar bloqueado
    return !cola_urgente.empty() || !cola_normal.empty();
}

void Pasteleria::agregar_a_cola(const Platillo& platillo) {
    pthread_mutex_lock(&mutex_colas);
    
    if (platillo.urgente) {
        imprimir("Cocinero " + to_string(platillo.id_cocinero) + 
                ": Platillo URGENTE '" + platillo.nombre_platillo + 
                "' agregado a cola prioritaria");
        cola_urgente.push(platillo);
    } else {
        imprimir("Cocinero " + to_string(platillo.id_cocinero) + 
                ": Platillo '" + platillo.nombre_platillo + 
                "' agregado a cola normal");
        cola_normal.push(platillo);
    }
    
    pthread_mutex_unlock(&mutex_colas);
}

void Pasteleria::hornear_platillo(int id_cocinero) {
    // 1. Esperar por un horno disponible
    imprimir("Cocinero " + to_string(id_cocinero) + ": Esperando horno disponible...");
    sem_wait(&hornos_disponibles);
    
    // 2. Obtener el siguiente platillo de la cola
    pthread_mutex_lock(&mutex_colas);
    
    if (!hay_platillos_esperando()) {
        pthread_mutex_unlock(&mutex_colas);
        sem_post(&hornos_disponibles);
        return;
    }
    
    Platillo platillo = obtener_siguiente_platillo();
    pthread_mutex_unlock(&mutex_colas);
    
    // 3. Asignar un horno específico
    pthread_mutex_lock(&mutex_hornos);
    int num_horno = asignar_horno();
    pthread_mutex_unlock(&mutex_hornos);
    
    // 4. Hornear (sección crítica)
    imprimir("Cocinero " + to_string(platillo.id_cocinero) + 
            ": Horneando '" + platillo.nombre_platillo + 
            "' en horno " + to_string(num_horno) + 
            " por " + to_string(platillo.tiempo_horneado) + " segundos");
    
    sleep(platillo.tiempo_horneado);
    
    // 5. Liberar el horno
    pthread_mutex_lock(&mutex_hornos);
    liberar_horno(num_horno);
    pthread_mutex_unlock(&mutex_hornos);
    
    imprimir("Cocinero " + to_string(platillo.id_cocinero) + 
            ": Platillo '" + platillo.nombre_platillo + 
            "' terminado. Horno " + to_string(num_horno) + " liberado");
    
    // 6. Señalar que hay un horno disponible
    sem_post(&hornos_disponibles);
}