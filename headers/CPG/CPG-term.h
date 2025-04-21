#pragma once
/**
 * @file CPG-term.h
 * @brief Cross-platform terminal/console utilities (printf style).
 *
 * Provides simple functions for manipulating the terminal, such as setting text color,
 * clearing the screen, and getting terminal size. Supports both Windows and POSIX systems.
 *
 * Namespace: CPG_term
 *
 * Provided functions:
 * - set_color : Set terminal text color
 * - reset_color : Reset text color to default
 * - clear      : Clear the terminal screen
 * - get_size   : Get terminal width and height (columns, rows)
 *
 * Includes:
 * <string> <utility>
 * #Windows: <windows.h>
 * #POSIX: <sys/ioctl.h>, <unistd.h>
 *
 * @author CodinPanGuin
 * @date 2025-04-21
 * @version 1.0
 * @note License: MIT
 */

#include <string>
#include <utility>

#if defined(_WIN32)
  #include <windows.h>
#else
  #include <sys/ioctl.h>
  #include <unistd.h>
#endif

namespace CPG_term {
  enum class Color {
    Default, 
    Red, Green, Yellow, Blue, Magenta, Cyan, Gray , White, Black,
    LGRed, LGGreen, LYellow, LBlue, LMagenta, LCyan, LGray
  };
  /**
  * @brief Set terminal text color (foreground only).
  * @code
  * CPG_term::set_color(CPG_term::Color::White);
  * @endcode
  * @param color The color to set for the terminal text.
  * @return None.
   */
  inline void set_color(Color color) {
    switch (color) {
      case Color::Black:   printf("\033[30m"); break;
      case Color::Red:     printf("\033[31m"); break;
      case Color::Green:   printf("\033[32m"); break;
      case Color::Yellow:  printf("\033[33m"); break;
      case Color::Blue:    printf("\033[34m"); break;
      case Color::Magenta: printf("\033[35m"); break;
      case Color::Cyan:    printf("\033[36m"); break;
      case Color::Gray:    printf("\033[90m"); break;
      case Color::White:   printf("\033[37m"); break;
      case Color::LGRed:   printf("\033[91m"); break;
      case Color::LGGreen: printf("\033[92m"); break;
      case Color::LYellow: printf("\033[93m"); break;
      case Color::LBlue:   printf("\033[94m"); break;
      case Color::LMagenta:printf("\033[95m"); break;
      case Color::LCyan:   printf("\033[96m"); break;
      case Color::LGray:   printf("\033[97m"); break;
      case Color::Default: printf("\033[0m");  break;
    }
  }

  /**
   * @brief Reset terminal text color to default.
   * @code
   * CPG_term::reset_color();
   * @endcode
   * @return None.
   */
  inline void reset_color() {
    printf("\033[0m");
  }

  /**
   * @brief Clear the terminal screen.
   * @code
   * CPG_term::clear();
   * @endcode
   * @return None.
   */
  inline void clearsc() {
    printf("\033[2J\033[H");
  }

  /**
   * @brief Get the size of the terminal (width and height).
   * @code
   * auto [width, height] = CPG_term::get_size();
   * int cols = width;
   * int rows = height;
   * printf("Terminal size: %d cols x %d rows\n", cols, rows);
   * @endcode
   * @return A pair containing the width (columns) and height (rows) of the terminal.
   */
  inline std::pair<int, int> get_size() {
    #if defined(_WIN32)
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
            return {csbi.srWindow.Right - csbi.srWindow.Left + 1,
                    csbi.srWindow.Bottom - csbi.srWindow.Top + 1};
        }
        return {80, 24};
    #else
      struct winsize ws;
      if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0) {
        return {ws.ws_col, ws.ws_row};
      }
      return {80, 24};
    #endif
  }
}