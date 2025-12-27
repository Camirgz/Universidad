// Copyright 2024 ECCI-UCR CC-BY-4
#include <random>

/**
 * @brief Generates pseudorandom numbers using a uniform distribution
 * @tparam Num The data type of the numbers
 * @code
 * UniformRandom<int> uniformRandom;
 * std::cout << "Your lucky number is " << uniformRandom.between(0, 100);
 * @endcode
 */
template <typename Num>
class UniformRandom {
 private:
  /// Try to get a seed from hardware, if available
  std::random_device::result_type seed;
  /// Generates pseudo-randon numbers using the Mersenne-Twister algoritym
  std::mt19937 randomEngine;

 public:
  /// Constructor
  explicit UniformRandom(const Num seedAddition = 0)
    : seed{std::random_device()()}
    , randomEngine{seed + seedAddition} {
  }
  /// Generates an uniform pseudo-random number in the range [min, max[
  Num between(const Num min, const Num max) {
    // Produce random values with uniform discrete distribution
    std::uniform_int_distribution<Num> randomDistribution(min, max - 1);
    // Generate and return a random number using the uniform distribution
    return randomDistribution(randomEngine);
  }
};
