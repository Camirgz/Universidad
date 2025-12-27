// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4

#ifndef SIMULATION_H
#define SIMULATION_H

// Error codes
#define ERR_UNIT_COUNT 1
#define ERR_PRODUCER_COUNT 2
#define ERR_CONSUMER_COUNT 3
#define ERR_MIN_PROD_DELAY 4
#define ERR_MAX_PROD_DELAY 5
#define ERR_MIN_CONS_DELAY 6
#define ERR_MAX_CONS_DELAY 7
#define ERR_NO_ARGS 8
#define ERR_CREATE_THREAD 1

// Feature test macros
#define _POSIX_C_SOURCE 200809L

// Includes
#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/random.h>
#include <stdio.h>
#include <sys/time.h>

typedef struct simulation simulation_t;  // Estructura opaca

simulation_t* simulation_create();

int simulation_run(simulation_t* simulation, int argc, char* argv[]);

void simulation_destroy(simulation_t* simulation);

#endif  // SIMULATION_H
