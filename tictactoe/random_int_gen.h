#include <random>

#ifndef RANDOM_INT_GEN_H
#define RANDOM_INT_GEN_H

// Initialize the random generator once
std::mt19937 generator(std::random_device{}());

/**
 * @brief Generate a random integer between min and max (inclusive).
 *
 * @param min The minimum value of the random number.
 * @param max The maximum value of the random number.
 * @return A random integer between min and max.
 */
int GetRandomNum(const int min, const int max) {
  std::uniform_int_distribution<int> distribution(min, max);
  return distribution(generator);
}

#endif // RANDOM_INT_GEN_H