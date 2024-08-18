// This code is an adaptation of the code from the following link:
// https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal

#ifndef COLORMOD_H
#define COLORMOD_H

#include <ostream>

namespace Color {
  enum Code {
    FG_RED      = 31, // Red foreground color code
    FG_GREEN    = 32, // Green foreground color code
    FG_YELLOW   = 33, // Yellow foreground color code
    FG_BLUE     = 34, // Blue foreground color code
    FG_MAGENTA  = 35, // Magenta foreground color code
    FG_CYAN     = 36, // Cyan foreground color code
    FG_DEFAULT  = 39, // Default foreground color code
    BG_RED      = 41, // Red background color code
    BG_GREEN    = 42, // Green background color code
    BG_YELLOW   = 43, // Yellow background color code
    BG_BLUE     = 44, // Blue background color code
    BG_MAGENTA  = 45, // Magenta background color code
    BG_CYAN     = 46, // Cyan background color code
    BG_DEFAULT  = 49  // Default background color code
  };

  class Modifier {
   public:
    Modifier(Code pCode) : code_(pCode) {}
    friend std::ostream& operator<<(std::ostream& os, const Modifier& mod) {
      return os << "\033[" << mod.code_ << "m";
    }
   private:
    Code code_;
  };
}

#endif // COLORMOD_H