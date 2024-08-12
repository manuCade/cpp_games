#include <cstdlib>
#include <string>

#ifndef CLEAR_SCREEN_H_
#define CLEAR_SCREEN_H_

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

# endif // CLEAR_SCREEN_H_