// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4

#include <stdlib.h>
#include <sys/types.h>
#include "common.h"
#include <unistd.h>  

int random_between(int min, int max) {
  // Si max es mayor que min, generar un número aleatorio en el rango, sino devolver min
  return min + (max > min ? (random() % (max - min)) : 0);
}
