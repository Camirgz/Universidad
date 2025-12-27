// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0
#include <omp.h>
#include <iostream>
#include <vector>

void print_mapping(const char* type, const std::vector<int>& mapping);

int main(int argc, char* argv[]) {
  int thread_count = omp_get_max_threads();
  if (argc >= 2) {
    thread_count = atoi(argv[1]);
  }

  int iteration_count = thread_count;
  if (argc >= 3) {
    iteration_count = atoi(argv[2]);
  }

  int block_size = 0;
  if (argc >= 4) {
    block_size = atoi(argv[3]);
  }

  std::vector<int> mapping(iteration_count);

  #pragma omp parallel num_threads(thread_count) \
    default(none) shared(iteration_count, mapping, block_size)
  {
    if (block_size == 0) {
      #pragma omp for schedule(static)
      for (int iteration = 0; iteration < iteration_count; ++iteration) {
        mapping[iteration] = omp_get_thread_num();
      }

      #pragma omp single
      print_mapping("static    ", mapping);

      #pragma omp for schedule(dynamic)
      for (int iteration = 0; iteration < iteration_count; ++iteration) {
        mapping[iteration] = omp_get_thread_num();
      }

      #pragma omp single
      print_mapping("dynamic   ", mapping);

      #pragma omp for schedule(guided)
      for (int iteration = 0; iteration < iteration_count; ++iteration) {
        mapping[iteration] = omp_get_thread_num();
      }

      #pragma omp single
      print_mapping("guided    ", mapping);
    } else {
      #pragma omp for schedule(static, block_size)
      for (int iteration = 0; iteration < iteration_count; ++iteration) {
        mapping[iteration] = omp_get_thread_num();
      }

      #pragma omp single
      print_mapping("static,N  ", mapping);

      #pragma omp for schedule(dynamic, block_size)
      for (int iteration = 0; iteration < iteration_count; ++iteration) {
        mapping[iteration] = omp_get_thread_num();
      }

      #pragma omp single
      print_mapping("dynamic,N ", mapping);

      #pragma omp for schedule(guided, block_size)
      for (int iteration = 0; iteration < iteration_count; ++iteration) {
        mapping[iteration] = omp_get_thread_num();
      }

      #pragma omp single
      print_mapping("guided,N  ", mapping);
    }
  }
}

void print_mapping(const char* type, const std::vector<int>& mapping) {
  std::cout << type;
  for (size_t index = 0; index < mapping.size(); ++index) {
    std::cout << mapping[index] << (index == mapping.size() - 1 ? '\n' : ' ');
  }
}
