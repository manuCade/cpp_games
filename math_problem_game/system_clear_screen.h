#include <cstdlib> // For std::system
#include <string>  // For std::string

#pragma once

namespace Console {
  /**
   * @brief Clears the console screen.
   *
   * This function uses the appropriate system command to clear the console screen.
   * On Windows, it uses the "cls" command, and on other platforms, it uses the "clear" command.
   */
  void ClearScreen() {
  #ifdef _WIN32
  std::system("cls");
  #else
  std::system("clear");
  #endif
  }
}

