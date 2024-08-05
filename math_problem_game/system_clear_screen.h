#include <cstdlib> // For std::system
#include <string>  // For std::string

#ifndef SYSTEM_CLEAR_H_
#define SYSTEM_CLEAR_H_

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

#endif // SYSTEM_CLEAR_H_