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
 * @brief Emojify function adds an emoji representation of a num to a given message.
 * 
 * @param num The num to be emojified. It should be an integer between 1 and 5.
 * @return The emoji representation of the num.
 */
std::string Emojify(const int num) {
  switch (num) {
  case 1:
    return "🍊";
  case 2:
    return "🍇";
  case 3:
    return "🍋";
  case 4:
    return "🍎";
  case 5:
    return "🥥";
  default:
    return "";
  }
}

/**
 * @brief Executes a single round of the game.
 *        This function generates three random numbers between 1 and 5, and then 
 *        converts them into emojis to print the series as a slot machine.
 * @return true if all three numbers are equal (player wins), false otherwise.
 */
bool GameRound() {
  const int num1{GetRandom(1, 5)}, num2{GetRandom(1, 5)}, num3{GetRandom(1, 5)};
  std::cout << '\n' << SlowlyPrintingString{Emojify(num1), 300} << " | ";
  std::cout << SlowlyPrintingString{Emojify(num2), 300} << " | ";
  std::cout << SlowlyPrintingString{Emojify(num3), 300} << "\n";
  return (num1 == num2 && num2 == num3);
}

int main() {
  const bool win{true};
  std::cout << "Let's gamble!\n";
  char option;
  std::cin >> option;
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  if (tolower(option) == 'n') return 0;
  while (true) {
    if (GameRound() == win) {
      std::cout << "\nYEAH!" << std::endl;
      break;
    } else {
      std::cout << "\nAw, dang it!" << std::endl;
      std::cout << "Do you want to play again? [any letter/n]: ";
      std::cin >> option;
      if (tolower(option) == 'n') return 0;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}