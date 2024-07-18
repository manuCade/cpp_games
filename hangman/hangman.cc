#include <string>
#include <random>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "system_clear_screen.h"

const int win = true;

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
 * @brief Count the number of lines in a file.
 * 
 * @param input_file_name The name of the input file.
 * @return The number of lines in the file. Returns 0 if the file cannot be opened.
 */
int GetNumLinesFromFile(const std::string& input_file_name) {
    std::ifstream input_file(input_file_name); 
    if (!input_file.is_open()) return 0;
    return std::count(std::istreambuf_iterator<char>(input_file),
                      std::istreambuf_iterator<char>(), '\n');
}

/**
 * @brief Retrieve a random word from a file.
 * 
 * @param input_file_name The name of the input file.
 * @return A random word from the file, or an empty string if the file cannot be opened.
 */
std::string RandomWordFromFile(const std::string& input_file_name) {
  std::ifstream input_file(input_file_name); 
  if (!input_file.is_open()) return "";
  const int num_lines{GetNumLinesFromFile(input_file_name)};
  const int target_line{GetRandomNum(0, num_lines)};
  int currentLine{0};
  std::string line;
  while (std::getline(input_file, line)) {
    if (++currentLine == target_line) break;
  }
  std::istringstream line_stream(line);
  std::string word{};
  // A line can have multiple words, so we get the first one
  line_stream >> word;
  input_file.close();
  return word;
}


/**
 * @brief Prints the hangman figure based on the number of attempts remaining.
 *
 * @param num_attempts The number of attempts remaining.
 */
void PrintHangman(const int num_attemps) {
  switch (num_attemps) {
    case 9:
      std::cout << "                  \n";
      std::cout << "                  \n";
      std::cout << "                  \n";
      std::cout << "                  \n";
      std::cout << "                  \n";
      std::cout << "                  \n";
      std::cout << "                  \n";
      std::cout << "   ____________   \n";

      break;
    case 8:
      std::cout << "                  \n";
      std::cout << "  |               \n";
      std::cout << "  |               \n";
      std::cout << "  |               \n";
      std::cout << "  |               \n";
      std::cout << "  |               \n";
      std::cout << "  |               \n";
      std::cout << "  |____________   \n";
      break;
    case 7:
      std::cout << " --------------   \n";
      std::cout << "  |               \n";
      std::cout << "  |               \n";
      std::cout << "  |               \n";
      std::cout << "  |               \n";
      std::cout << "  |               \n";
      std::cout << "  |               \n";
      std::cout << "  |____________   \n";
      break;
    case 6:
      std::cout << " --------------   \n";
      std::cout << "  |          |    \n";
      std::cout << "  |          @    \n";
      std::cout << "  |               \n";
      std::cout << "  |               \n";
      std::cout << "  |               \n";
      std::cout << "  |               \n";
      std::cout << "  |               \n";
      std::cout << "  |____________   \n";
      break;
    case 5:
      std::cout << " --------------   \n";
      std::cout << "  |          |    \n";
      std::cout << "  |          @    \n";
      std::cout << "  |          |    \n";
      std::cout << "  |          |    \n";
      std::cout << "  |               \n";
      std::cout << "  |               \n";
      std::cout << "  |____________   \n";
      break;
    case 4:
      std::cout << " --------------   \n";
      std::cout << "  |          |    \n";
      std::cout << "  |          @    \n";
      std::cout << "  |         /|    \n";
      std::cout << "  |          |    \n";
      std::cout << "  |               \n";
      std::cout << "  |               \n";
      std::cout << "  |____________   \n";
      break;
    case 3:
      std::cout << " --------------   \n";
      std::cout << "  |          |    \n";
      std::cout << "  |          @    \n";
      std::cout << "  |         /|\\   \n";
      std::cout << "  |          |    \n";
      std::cout << "  |               \n";
      std::cout << "  |               \n";
      std::cout << "  |____________   \n";
      break;
    case 2:
      std::cout << " --------------   \n";
      std::cout << "  |          |    \n";
      std::cout << "  |          @    \n";
      std::cout << "  |         /|\\   \n";
      std::cout << "  |          |    \n";
      std::cout << "  |         /     \n";
      std::cout << "  |               \n";
      std::cout << "  |____________   \n";
      break;
    case 1:
      std::cout << " --------------   \n";
      std::cout << "  |          |    \n";
      std::cout << "  |          @    \n";
      std::cout << "  |         /|\\   \n";
      std::cout << "  |          |    \n";
      std::cout << "  |         / \\   \n";
      std::cout << "  |               \n";
      std::cout << "  |____________   \n";
      break;
    case 0:
      std::cout << " --------------   \n";
      std::cout << "  |          |    \n";
      std::cout << "  |          U    \n";
      std::cout << "  |         /|\\   \n";
      std::cout << "  |          |    \n";
      std::cout << "  |         / \\   \n";
      std::cout << "  |               \n";
      std::cout << "  |_____@______   \n";
      break;
  }
}

/**
 * @brief Print the current state of the game.
 *
 * @param guess_word The word with the guessed letters.
 * @param excluded_letters The letters that have been used but are not in the word.
 */
void PrintGame(const std::string& guess_word, const std::string& excluded_letters) {
  // print letters used
  std::cout << " Not valid letters: ";
  for (int i = 0; !excluded_letters.empty() && i < excluded_letters.length() - 1; ++i) {
    std::cout << excluded_letters[i] << ", ";
  }
  std::cout << excluded_letters[excluded_letters.length() - 1] << '\n';
  // print guess word
  std::cout << '\n' << " ";
  for (const auto c : guess_word) {
    std::cout << c << " ";
  }
  std::cout << "\n\n";
}

/**
 * @brief Play a round of the game.
 * 
 * @param input_file_name The name of the input file.
 * @param num_attemps The number of attempts remaining.
 * @param word The target word to guess.
 * @param guess_word The current guessed word.
 * @param excluded_letters The letters that are not in the word.
 * @return True if the guess is correct and the game is won, false otherwise.
 */
bool GameRound(const std::string& input_file_name, int& num_attemps, const std::string& word, 
               std::string& guess_word, std::string& excluded_letters) {
    std::cout << " Write a letter (press enter): ";
    // Ask user
    char guess_letter;
    std::cin >> guess_letter;
    guess_letter = toupper(guess_letter);
    Console::ClearScreen();
    // Check if its a letter
    if (!isalpha(guess_letter)) {
      std::cout << guess_letter << " is not a valid letter\n";
      ++num_attemps; // to keep the number of attemps
      return false;
    }
    // Check if the letter is in excluded_letters bank
    if (excluded_letters.find(guess_letter) != std::string::npos ||
        guess_word.find(guess_letter) != std::string::npos) {
      std::cout << " This letter was already used\n";
      ++num_attemps; // to keep the number of attemps
      return false;
    }
    // Update the guess_word
    bool in_word = false;
    for (int i = 0; i < word.length(); ++i)
      if (guess_letter == word[i]) {
        guess_word[i] = word[i];
        in_word = true;
      }
    if (!in_word) excluded_letters += guess_letter;
    else num_attemps++;
    // Checks the win
    return guess_word == word;
}

/**
 * @brief Runs the game loop for the Hangman game.
 *
 * @param vocabulary_file_name The name of the file containing the vocabulary of words.
 * @return Returns true if the player wins the game, false otherwise.
 */
bool Game(const std::string& vocabulary_file_name) {
  int num_attemps = 9;
  // Gets the word from the file
  std::string generated_word = RandomWordFromFile(vocabulary_file_name);
  if (generated_word.empty()) {
    std::cerr << "There was an error trying to get the word\n";
    return 1;
  }
  for (auto& c : generated_word) c = toupper(c);
  // The `guess_word` characters are replaced with the word's characters if the
  // user got it right until `guess_word` is equal to the word.
  std::string guess_word(generated_word.length(), '_');
  std::string excluded_letters{};
  Console::ClearScreen();
  PrintGame(guess_word, excluded_letters);
  PrintHangman(num_attemps);
  while (num_attemps--) {
    bool status = GameRound(vocabulary_file_name, num_attemps, generated_word, guess_word, excluded_letters);
    PrintGame(guess_word, excluded_letters);
    PrintHangman(num_attemps);
    if (status) return win;
  }
  return !win;
}

int main() {
  const std::string vocabulary_file_name = "hangman_en.txt";
  std::cout << (Game(vocabulary_file_name) == win ? "Congratulations! You won!" : "Game over!") << std::endl;
}