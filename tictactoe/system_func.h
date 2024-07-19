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

  /**
   * @brief Sleeps for a given number of seconds.
   *
   * This function uses the appropriate system command to sleep for a given number of seconds.
   * On Windows, it uses the "timeout" command, and on other platforms, it uses the "sleep" command.
   *
   * @param seconds The number of seconds to sleep.
   */
  void Sleep(int seconds) {
  #ifdef _WIN32
  std::system(("timeout /t " + std::to_string(seconds)).c_str());
  #else
  std::system(("sleep " + std::to_string(seconds)).c_str());
  #endif
  }
}

