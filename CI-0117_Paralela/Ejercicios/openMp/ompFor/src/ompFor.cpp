// Copyright 2024 ECCI-UCR CC-BY 4.0
#include <iostream>

int main(int argc, char* argv[]) {
  const int thread_count = argc >= 2 ? ::atoi(argv[1]) : 1;
  const int iteration_count = argc >= 3 ? ::atoi(argv[2]) : thread_count;

  for (int iteration = 0; iteration < iteration_count; ++iteration) {
    std::cout << 0 << '/' << thread_count
      << ": iteration " << iteration << '/' << iteration_count << std::endl;
  }
}
