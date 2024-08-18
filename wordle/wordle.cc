#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "colormod.h"

std::mt19937 generator(std::random_device{}());

int GetRandomNum(const int min, const int max) {
  std::uniform_int_distribution<int> distribution(min, max);
  return distribution(generator);
}

int GetNumLinesFromFile(const std::string& input_file_name) {
    std::ifstream input_file(input_file_name); 
    if (!input_file.is_open()) return 0;
    return std::count(std::istreambuf_iterator<char>(input_file),
                      std::istreambuf_iterator<char>(), '\n');
}

std::string RandomWordFromFile(const std::string& input_file_name) {
  std::ifstream input_file(input_file_name); 
  if (!input_file.is_open()) return "";
  const int num_lines{GetNumLinesFromFile(input_file_name)};
  int target_line{GetRandomNum(0, num_lines)}, currentLine{0};
  std::string line;
  while (std::getline(input_file, line))
    if (++currentLine == target_line) break;
  std::istringstream line_stream(line);
  std::string word;
  line_stream >> word;
  input_file.close();
  return word;
}

void PrintGame(const std::string& word, const std::string& letters_tried,
               const std::vector<std::pair<std::string, std::string>>& words_tried) {
  // Print used letters
  std::cout << "Intentos disponibles: " << 6 - words_tried.size() << "\n\n";
  std::cout << "Letras utilizadas: ";
  for (size_t i = 0; !letters_tried.empty() && i < letters_tried.length() - 1; ++i)
    std::cout << letters_tried[i] << ", ";
  std::cout << letters_tried[letters_tried.length() - 1] << "\n\n";
  // Print words tried
  Color::Modifier green(Color::FG_GREEN);
  Color::Modifier yellow(Color::FG_YELLOW);
  Color::Modifier def(Color::FG_DEFAULT);
  for (const auto& guess : words_tried) {
    std::cout << "        ";
    for (size_t i = 0; i < guess.first.length(); ++i) {
      if (guess.second[i] == 'G')
        std::cout << green << guess.first[i] << def;
      else if (guess.second[i] == 'Y') 
        std::cout << yellow << guess.first[i] << def;
      else
        std::cout << guess.first[i];
      std::cout << " ";
    }
    std::cout << std::endl;
  }
}

std::string CheckColors(const std::string& og_word, const std::string& guess) {
  std::string word{og_word};
  std::string guess_color(guess.length(), 'W');
  // Check for correct positions
  for (size_t i = 0; i < guess.length(); ++i) {
    if (guess[i] == word[i]) {
      guess_color[i] = 'G';
      word[i] = '_'; // Mark this letter as used
    }
  }
  // Check for correct letters in wrong positions
  for (size_t i = 0; i < guess.length(); ++i) {
    if (guess_color[i] == 'G') continue; // Skip already correctly guessed letters
    auto index = std::find(word.begin(), word.end(), guess[i]);
    if (index != word.end()) {
      guess_color[i] = 'Y';
      *index = '_'; // Mark this letter as used
    }
  }
  return guess_color;
}

bool GameRound(int& num_attemps, const std::string& word, std::string& letters_tried, 
               std::vector<std::pair<std::string, std::string>>& words_tried) {
  // Ask user guessed word
  std::cout << "        ";
  std::string guess;
  std::cin >> guess;
  system("clear");
  // Upper the guess word because the word is in uppercase
  for (char& c : guess) c = toupper(c);
  if (guess.length() != word.length()) {
    std::cout << "Invalid word, must be a five letter word!" << std::endl;
    num_attemps++;
    return false;
  }
  // Save the word in words_tried
  words_tried.push_back(std::make_pair(guess, CheckColors(word, guess)));
  // Save letters used in letters_tried
  for (size_t i{0}; i < guess.length(); ++i)
    if (std::find(letters_tried.begin(), letters_tried.end(), guess[i]) == letters_tried.end())
      letters_tried += guess[i];
  return guess == word;
}

const bool win{true};

bool Game(const std::string& vocabulary_file_name, int num_attemps) {
  system("clear");
  // Get the word from the file
  std::string word = RandomWordFromFile(vocabulary_file_name);
  if (word.empty()) {
    std::cerr << "There was an error trying to get the word\n";
    exit(EXIT_FAILURE);
  }
  for (char& c : word) c = toupper(c);
  std::string guess_word(word.length(), '_');
  std::string letters_tried;
  std::vector<std::pair<std::string, std::string>> words_tried{};
  bool status{false};
  PrintGame(word, letters_tried, words_tried);
  while (num_attemps--) {
    status = GameRound(num_attemps, word, letters_tried, words_tried);
    PrintGame(word, letters_tried, words_tried);
    if (status == win) return win;
  }
  return !win;
}

int main() {
  const int num_attemps{6};
  const std::string vocabulary_file_name{"wordle_vocab.txt"};
  std::cout << (Game(vocabulary_file_name, num_attemps) ? 
  "Congratulations!!!" : "Better luck next time...");
  std::cout << std::endl;
}