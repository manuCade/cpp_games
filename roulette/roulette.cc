#include <random>
#include <chrono>
#include <thread>
#include <iostream>
#include <string>

/**
 * @brief Structure representing a string that is printed slowly with a delay between each character.
 */
struct SlowlyPrintingString {
  std::string data; // The string to be printed slowly.
  long int delay;   // The delay (in milliseconds) between each character.
};

/**
 * @brief Overload the << operator to print SlowlyPrintingString objects character by character with a delay.
 *
 * @param os The output stream to print to.
 * @param str The SlowlyPrintingString object to be printed.
 * @return The output stream after printing the SlowlyPrintingString object.
 */
std::ostream& operator<<(std::ostream& os, const SlowlyPrintingString& str) {
  for (const auto& c : str.data) {
    os << c << std::flush;        
    std::this_thread::sleep_for(std::chrono::milliseconds(str.delay));
  }
  return os;
}

// Initialize the random generator once
std::mt19937 generator(std::random_device{}());

/**
 * @brief Generate a random integer between min and max (inclusive).
 *
 * @param min The minimum value of the random number.
 * @param max The maximum value of the random number.
 * @return A random integer between min and max.
 */
int GetRandom(const int min, const int max) {
  std::uniform_int_distribution<int> distribution(min, max);
  return distribution(generator);
}

/**
 * @brief Executes a single round of the game.
 *        This function prompts the user to choose a number between 0 and 32, 
 *        and then generates a random number.
 * 
 * @return true if the user's chosen number matches the generated random number, false otherwise.
 */
int GameRound() {
  std::cout << "\nChoose a number (0 - 32): ";
  int num{-1};
  std::cin >> num;
  if (std::cin.fail() || num < 0 || num > 32) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return -1;
  }
  int random_number = GetRandom(0, 32);
  std::cout << "The ball falls in" << SlowlyPrintingString{" ... ", 500};
  std::cout << random_number << " \t\t";
  return num == random_number;
}

int main() {
  const bool win{true};
  std::cout << "Let's gamble!" << std::endl;
  char option;
  while (true) {
    if (GameRound() == win) {
      std::cout << "\nYou are a winner!" << std::endl;
    } else if (!win) {
      std::cout << "Aw, dang it!" << std::endl;
    } else {
      std::cout << "Choose a valid number!" << std::endl;
    }
    std::cout << "Do you want to play again? [any letter/n]: ";
    std::cin >> option;
    if (tolower(option) == 'n') break;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}
