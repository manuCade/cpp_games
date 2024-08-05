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
#include "system_clear_screen.h"
#include "random_int_gen.h"

const int rows{10}, cols{rows - 1}, monsters{rows - 2};
struct Status {
  bool has_monster = false;
  bool been_discovered = false;
};

struct Player {
  int row{0};
  int col{0};
  int tries{1};
};

typedef std::vector<std::vector<Status>> matrix;

void InitializeGrid(matrix& grid) {
  for (int i{1}; i < rows - 1; ++i) {
    int monster_column_position = GetRandomInt(0, cols - 1);
    bool can_place_monster = true;
    // Check if in the same column there are a monster already
    // so k is equivalent of rows
    for (int k{1}; k < rows - 1; ++k) {
      if (grid[k][monster_column_position].has_monster == true) {
        can_place_monster = false;
        break;
      }
    }
    if (can_place_monster) {
      grid[i][monster_column_position].has_monster = true;
    } else {
      monster_column_position = GetRandomInt(0, cols - 1);
      --i;
    }
  }
}

void PrintGrid(const Player player, const matrix& grid) {
  std::cout << "Tries: " << player.tries << std::endl;
  for (int i{0}; i < rows; ++i) {
    // Print the top part of cell
    for (int j{0}; j < cols; ++j) std::cout << "+----";
    std::cout << "+\n";
    // Print the content of the cell
    for (int j{0}; j < cols; ++j) {
      std::cout << "|";
      if (grid[i][j].has_monster == true && grid[i][j].been_discovered == true) {
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

void UserInput(Player& player) {
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
}

void PlayerCollided(Player& player, matrix& grid) {
  if (grid[player.row][player.col].has_monster == true) {
    grid[player.row][player.col].been_discovered = true;
    player.row = 0;
    player.col = 0;
    ++player.tries;
  }
}

void Game(Player& player, matrix& grid) {
  InitializeGrid(grid);
  while (player.row < rows - 1) {
    Console::ClearScreen();
    PrintGrid(player, grid);
    UserInput(player);
    PlayerCollided(player, grid);
  }
  Console::ClearScreen();
  PrintGrid(player, grid);
}

int main() {
  matrix grid(rows, std::vector<Status>(rows, {false, false}));
  Player player;
  Game(player, grid);
  std::cout << "You won!" << std::endl;
}