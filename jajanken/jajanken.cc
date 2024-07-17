#include <iostream>
#include <string>
#include <random>

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

/**
 * @brief Enumerates the possible choices in the Jajanken game.
 */
enum Jajanken { rock = 1, paper = 2, scissors = 3 };

/**
 * @brief Checks the result of a round of the Jajanken game.
 *
 * @param user_choice The user's choice (rock, paper, or scissors).
 * @param game_choice The AI's choice (rock, paper, or scissors).
 * @return 1 if the user wins, -1 if the AI wins, 0 if it's a tie.
 */
int CheckWin(const Jajanken user_choice, const int game_choice) {
  if (user_choice == game_choice) return 0;
  // As ties are considered before, we can only win or lose
  if (user_choice == rock) return game_choice == scissors ? 1 : -1;
  if (user_choice == paper) return game_choice == rock ? 1 : -1;
  if (user_choice == scissors) return game_choice == paper ? 1 : -1;
  return 0;
}

/**
 * @brief Converts the Jajanken choice to its corresponding emoji.
 *
 * @param choice The Jajanken choice (rock, paper, or scissors).
 * @return The emoji representation of the choice.
 */
std::string Emojify(const Jajanken choice) {
  if (choice == rock) return "🪨";
  if (choice == paper) return "📃";
  if (choice == scissors) return "✂️";
  return "";
}

/**
 * @brief Executes a round of the Jajanken game.
 *
 * @return 1 if the user wins, -1 if the AI wins, 0 if it's a tie.
 */
int GameRound() {
  std::cout << "🪨 (1), 📃 (2) or ✂️ (3): ";
  int user_input;
  std::cin >> user_input;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cerr << "Input error, not an integer!" << std::endl;
    return 0;
  } else if (user_input < 1 || user_input > 3) {
    std::cerr << "This number is not valid, must be 1, 2 or 3";
    return 0;
  }
  Jajanken user_choice = static_cast<Jajanken>(user_input);
  Jajanken game_choice = static_cast<Jajanken>(GetRandomNum(1, 3));
  std::cout << std::endl << "You " << Emojify(user_choice) << "   " << Emojify(game_choice) << "  AI";
  return CheckWin(user_choice, game_choice);
}

int main() {
  int wins{0}, loses{0}, ties{0}, status_round{0};
  std::cout << "Win 3 times to get the victory!" << std::endl;
  while (true) {
    status_round = GameRound();
    if (status_round == 1) ++wins;
    else if (status_round == -1) ++loses;
    else ++ties;
    std::cout << "\n     " << wins << " - " << loses << "\n\n";
    if (wins >= 3) {
      std::cout << "User wins!" << std::endl;
      return 0;
    } else if (loses >= 3) {
      std::cout << "AI wins!" << std::endl;
      return 0;
    } else if (ties >= 100) {
      std::cout << "You have invoked a black hole, congratulations!" << std::endl;
      return 0;
    }
  }
}