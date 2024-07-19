#include <limits>
#include <iostream>
#include <vector>
#include "system_func.h"
#include "random_int_gen.h"

enum Form {
  nothing = 0,
  circle = 1,
  cross = 2
};

enum Cell {
  up_left = 0,
  up_center = 1,
  up_right = 2,
  middle_left = 3,
  middle_center = 4,
  middle_right = 5,
  down_left = 6,
  down_center = 7,
  down_right = 8
};

/**
 * @brief Prints the Tic Tac Toe grid.
 *
 * @param grid The grid representing the Tic Tac Toe board, where each element is a pair of a Cell and a Form.
 */
void PrintGrid(const std::vector<std::pair<Cell, Form>>& grid) {
  std::cout << '\n';
  for (const auto& cell : grid) {
    if (cell.first != up_left && cell.first != middle_left && cell.first != down_left) {
      std::cout << " | ";
    }
    std::cout << (cell.second == circle ? 'O' : cell.second == cross ? 'X' : ' ');
    if (cell.first == up_right) {
      std::cout << "    0 1 2\n---------\n";
    } else if (cell.first == middle_right) {
      std::cout << "    3 4 5\n---------\n";
    } else if (cell.first == down_right) {
      std::cout << "    6 7 8\n";
    }
  }
}

/**
 * @brief Checks if three cells have the same form in the given grid.
 *
 * @param a The first cell index.
 * @param b The second cell index.
 * @param c The third cell index.
 * @param grid The grid containing the cells and their forms.
 * @return True if the three cells have the same form, false otherwise.
 */
bool HasSameForm(Cell a, Cell b, Cell c, const std::vector<std::pair<Cell, Form>>& grid) {
  return grid[a].second != nothing && grid[a].second == grid[b].second &&
         grid[b].second == grid[c].second;
}

/**
 * @brief Checks if the grid is full.
 *
 * @param grid The grid representing the Tic Tac Toe board, where each element is a pair of Cell and Form.
 * @return True if the grid is full, false otherwise.
 */
bool IsFull(const std::vector<std::pair<Cell, Form>>& grid) {
  for (const auto& cell : grid) {
    if (cell.second == nothing) return false;
  }
  return true;
}

/**
 * @brief Check if there is a win condition in the given grid.
 *
 * @param grid The grid representing the game board, where each element is a pair of Cell and Form.
 * @return An integer representing the win condition: 0 for no win, 1 for player 1 win, 2 for player 2 win.
 */
int CheckWin(const std::vector<std::pair<Cell, Form>>& grid) {
  // Horizontal wins
  if (HasSameForm(up_left, up_center, up_right, grid)) 
    return grid[up_left].second;
  if (HasSameForm(middle_left, middle_center, middle_right, grid)) 
    return grid[middle_left].second;
  if (HasSameForm(down_left, down_center, down_right, grid)) 
    return grid[down_left].second;
  // Vertical wins
  if (HasSameForm(up_left, middle_left, down_left, grid)) 
    return grid[up_left].second;
  if (HasSameForm(up_center, middle_center, down_center, grid)) 
    return grid[up_center].second;
  if (HasSameForm(up_right, middle_right, down_right, grid)) 
    return grid[up_right].second;
  // Diagonal wins
  if (HasSameForm(up_left, middle_center, down_right, grid)) 
    return grid[up_left].second;
  if (HasSameForm(up_right, middle_center, down_left, grid)) 
    return grid[up_right].second;
  return nothing;
}

/**
 * Takes user input and updates the game grid accordingly.
 * 
 * @param grid The game grid represented by a vector of pairs, where each pair contains a cell and its form.
 * @return True if the user's turn was successful, false otherwise.
 */
bool UserTurn(std::vector<std::pair<Cell, Form>>& grid) {
  int user_input;
  std::cin >> user_input;
  Console::ClearScreen();
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cerr << "Input error, not an integer!" << std::endl;
    return false;
  } else if (user_input < 0 || user_input > 8) {
    std::cout << "This number is not valid, must be between 0 and 8" << std::endl;
    UserTurn(grid);
    return false;
  }
  Cell user_cell_choice{static_cast<Cell>(user_input)};
  if (grid[user_cell_choice].second != nothing) {
    std::cout << "This cell is already taken!" << std::endl;
    return false;
  } else {
    grid[user_cell_choice].second = circle;
  }
  return true;
}

/**
 * @brief The PC chooses randomly an option between the available cells.
 * 
 * @param grid The game grid represented as a vector of pairs, where each pair contains a Cell and a Form.
 * @return True if the game turn was successful, false otherwise.
 */
bool PCTurn(std::vector<std::pair<Cell, Form>>& grid) {
  if (IsFull(grid)) return false;
  Cell game_cell_choice{static_cast<Cell>(GetRandomNum(0, 8))};
  while (grid[game_cell_choice].second != nothing) {
    game_cell_choice = static_cast<Cell>(GetRandomNum(0, 8));
  }
  grid[game_cell_choice].second = cross;
  return true;
}

int main() {
  std::vector<std::pair<Cell, Form>> grid{
  {up_left, nothing},
  {up_center, nothing},
  {up_right, nothing},
  {middle_left, nothing},
  {middle_center, nothing},
  {middle_right, nothing},
  {down_left, nothing},
  {down_center, nothing},
  {down_right, nothing}
  };
  
  Console::ClearScreen();
  std::cout << "Welcome to Tic Tac Toe!" << std::endl;
  PrintGrid(grid);
  while (!IsFull(grid)) {
    bool user_chose = UserTurn(grid);
    PrintGrid(grid);
    if (!user_chose) continue;
    if (CheckWin(grid) == circle) {
      std::cout << "\nYou won!" << std::endl;
      return 0;
    }
    Console::Sleep(1);
    Console::ClearScreen();
    PCTurn(grid);
    PrintGrid(grid);
    if (CheckWin(grid) == cross) {
      std::cout << "\nYou lost!" << std::endl;
      return 0;
    }
  }
  // If while ends means the grid is full and neither user nor game won
  std::cout << "\nIt's a tie!" << std::endl;
}