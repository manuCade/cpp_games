// Turbo, un caracol, intenta cruzar un tablero de 2024 filas y 2023 columnas,
// donde 2022 casillas tienen monstruos ocultos. Cada fila excepto la primera 
// y la última tiene un monstruo, y cada columna puede tener como máximo uno. 
// Turbo puede moverse a casillas adyacentes y debe evitar los monstruos, 
// recordando dónde están. El objetivo es determinar la menor cantidad de 
// intentos necesarios para que Turbo llegue a la última fila, sin importar 
// la ubicación de los monstruos.
// En este caso, este una simulación del problema donde se puede demostrar la
// solución óptima en forma de juego.

#include <vector>
#include <iostream>
#include <random>
#include "system_clear_screen.h"

// Initialize the random generator once
std::mt19937 generator(std::random_device{}());

/**
 * @brief Generate a random integer between min and max (inclusive).
 *
 * @param min The minimum value of the random number.
 * @param max The maximum value of the random number.
 * @return A random integer between min and max.
 */
int GenerateRandomInt(const int min, const int max) {
  std::uniform_int_distribution<int> distribution(min, max);
  return distribution(generator);
}

const int rows{10}, cols{rows - 1}, monsters{rows - 2};

enum Status {
  empty = 0,
  monster = 1
};

typedef std::vector<std::vector<Status>> matrix;

void InitializeGrid(matrix& grid) {
  for (int i{1}; i < rows - 1; ++i) {
    int monster_column_position = GenerateRandomInt(0, cols - 1);
    bool can_place_monster = true;
    // Check if in the same column there are a monster already
    // so k is equivalent of rows
    for (int k{1}; k < rows - 1; ++k) {
      if (grid[k][monster_column_position] == monster) {
        can_place_monster = false;
        break;
      }
    }
    if (can_place_monster) {
      grid[i][monster_column_position] = monster;
    } else {
      monster_column_position = GenerateRandomInt(0, cols - 1);
      --i;
    }
  }
}

struct Player {
  int row{0};
  int col{0};
  int tries{1};
};

// Prints the grid lines to show the cells and the monsters
/**
 * @brief Prints the grid with player and monster positions.
 * 
 * This function prints the grid with the player and monster positions. 
 * It also displays the number of tries the player has made.
 * 
 * @param player The player object containing the player's position.
 * @param grid The matrix representing the game grid.
 * @param discovered_monsters A vector indicating whether each monster has 
 *                            been discovered or not.
 */
void PrintGrid(const Player player, const matrix& grid,
               const std::vector<bool>& discovered_monsters) {
  std::cout << "Tries: " << player.tries << std::endl;
  for (int i{0}; i < rows; ++i) {
    // Print the top part of cell
    for (int j{0}; j < cols; ++j) std::cout << "+----";
    std::cout << "+\n";
    // Print the content of the cell
    for (int j{0}; j < cols; ++j) {
      std::cout << "|";
      if (grid[i][j] == monster && discovered_monsters[i] == true) {
        std::cout << " 👹 ";
      } else if (player.row == i && player.col == j) {
        std::cout << " 🐌 ";
      } else {
        std::cout << "    ";
      }
    }
    std::cout << "|\n";
  }
  // Print the down part of the cell
  for (int j{0}; j < cols; ++j) std::cout << "+----";
  std::cout << "+\n";
}

/**
 * @brief Executes a round of the game logic.
 *
 * This function allows the player to move in the game grid based on the 
 * input direction.
 * The player can move left (l), right (r), up (u), or down (d).
 * If the player collides with a monster, the player's position is reset to 
 * the top-left corner of the grid,
 * and the number of tries is incremented.
 *
 * @param player The player object representing the current player.
 * @param grid The game grid represented by a matrix.
 * @param discovered_monsters A vector indicating whether each row of the grid 
 *                            has a discovered monster.
 */
void GameLogicRound(Player& player, const matrix& grid,
                    std::vector<bool>& discovered_monsters) {
  std::cout << "Move using (l, r, u, d): ";
  char direction;
  std::cin >> direction;
  switch (direction) {
    case 'l':
      if (player.col > 0) --player.col;
      break;
    case 'r':
      if (player.col < cols - 1) ++player.col;
      break;
    case 'u':
      if (player.row > 0) --player.row;
      break;
    case 'd':
      if (player.row < rows - 1) ++player.row;
      break;
  }
  // Check if player collided with a monster
  if (grid[player.row][player.col] == monster) {
    discovered_monsters[player.row] = true;
    player.row = 0;
    player.col = 0;
    ++player.tries;
  }
}

/**
 * @brief Executes the game logic for the math problem game.
 *
 * This function initializes the grid, clears the console screen, 
 * and prints the grid and discovered monsters.
 * It then enters a loop where the game logic is executed for each 
 * round until the player reaches the last row.
 * After each round, the console screen is cleared and the updated 
 * grid and discovered monsters are printed.
 *
 * @param grid The matrix representing the game grid.
 * @param discovered_monsters A vector indicating whether each monster has been discovered.
 * @param player The player object representing the current player.
 */
void Game(matrix& grid, std::vector<bool>& discovered_monsters,
          Player& player) {
  InitializeGrid(grid);
  while (player.row < rows - 1) {
    Console::ClearScreen();
    PrintGrid(player, grid, discovered_monsters);
    GameLogicRound(player, grid, discovered_monsters);
  }
  Console::ClearScreen();
  PrintGrid(player, grid, discovered_monsters);
}

int main() {
  matrix grid(rows, std::vector<Status>(rows, empty));
  std::vector<bool> discovered_monsters(rows);
  Player player;
  Game(grid, discovered_monsters, player);
  std::cout << "You won!" << std::endl;
}