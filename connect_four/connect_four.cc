#include <random>
#include <iostream>
#include <vector>

std::mt19937 generator(std::random_device{}());

int GetRandomInt(const int min, const int max) {
  std::uniform_int_distribution<int> distribution(min, max);
  return distribution(generator);
}

const int rows{6}, cols{7};

enum Connect {
  empty,
  yellow,
  red
};

bool IsGridFull(const std::vector<std::vector<Connect>>& grid) {
  for (const auto& row : grid)
    for (const auto& connect : row)
      if (connect == empty) return false;
  return true;
}

bool CheckWin(const std::vector<std::vector<Connect>>& grid) {
  // Check rows
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < cols - 3; ++j)
      if (grid[i][j] != empty && grid[i][j] == grid[i][j + 1] && 
          grid[i][j] == grid[i][j + 2] && grid[i][j] == grid[i][j + 3])
        return true;
  // Check columns
  for (int i = 0; i < rows - 3; ++i)
    for (int j = 0; j < cols; ++j)
      if (grid[i][j] != empty && grid[i][j] == grid[i + 1][j] && 
          grid[i][j] == grid[i + 2][j] && grid[i][j] == grid[i + 3][j])
        return true;
  // Check diagonals (top-left to bottom-right)
  for (int i = 0; i < rows - 3; ++i)
    for (int j = 0; j < cols - 3; ++j)
      if (grid[i][j] != empty && grid[i][j] == grid[i + 1][j + 1] && 
          grid[i][j] == grid[i + 2][j + 2] && grid[i][j] == grid[i + 3][j + 3])
        return true;
  // Check diagonals (top-right to bottom-left)
  for (int i = 0; i < rows - 3; ++i)
    for (int j = 3; j < cols; ++j)
      if (grid[i][j] != empty && grid[i][j] == grid[i + 1][j - 1] && 
          grid[i][j] == grid[i + 2][j - 2] && grid[i][j] == grid[i + 3][j - 3])
        return true;
  return false;
}

void UserInput(std::vector<std::vector<Connect>>& grid) {
  while (true) {
    std::cout << "Say the column (1 - 7): ";
    int user_input;
    std::cin >> user_input;
    --user_input;
    if (user_input < 0 || user_input > 6) {
      std::cout << "This number is not valid, must be between 1 and 7" << std::endl;
      continue;
    }
    if (grid[0][user_input] != empty) {
      std::cout << "This column is full!" << std::endl;
      continue;
    }
    for (int i{rows - 1}; i >= 0; --i) {
      if (grid[i][user_input] == empty) {
        grid[i][user_input] = yellow;
        return;
      }
    }
  }
}

void PCInput(std::vector<std::vector<Connect>>& grid) {
  while (true) {
    int pc_input = GetRandomInt(0, rows);
    if (grid[0][pc_input] != empty) continue;
    for (int i{rows - 1}; i >= 0; --i) {
      if (grid[i][pc_input] == empty) {
        grid[i][pc_input] = red;
        return;
      }
    }
  }
}

void PrintGrid(const std::vector<std::vector<Connect>>& grid) {
  std::cout << "\n";
  for (int i{0}; i < rows; ++i) {
    // Print the top part of cell
    if (i != 0) {
      for (int j{0}; j < cols; ++j) std::cout << "+----";
      std::cout << "+";
    }
    std::cout << "\n";
    // Print the content of the cell
    for (int j{0}; j < cols; ++j) {
      std::cout << "|";
      if (grid[i][j] == yellow) 
        std::cout << " 🟡 ";
      else if (grid[i][j] == red) 
        std::cout << " 🔴 ";
      else std::cout << "    ";
    }
    std::cout << "|\n";
  }
  // Print the down part of the cell
  for (int j{0}; j < cols; ++j) 
    std::cout << "+----";
  std::cout << "+\n";
}

int main() {
  std::vector<std::vector<Connect>> grid(rows, {cols, empty});
  while (!IsGridFull(grid)) {
    system("clear");
    PrintGrid(grid);
    UserInput(grid);
    if (CheckWin(grid)) {
      system("clear");
      PrintGrid(grid);
      std::cout << "You won!" << std::endl;
      return 0;
    }
    PCInput(grid);
    if (CheckWin(grid)) {
      system("clear");
      PrintGrid(grid);
      std::cout << "You lost!" << std::endl;
      return 0;
    }
  }
  std::cout << "It's a draw!" << std::endl;
}