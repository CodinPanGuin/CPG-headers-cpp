#include "CPG-term.h"

#if defined(_WIN32)
  #include <windows.h>
#else
  #include <sys/ioctl.h>
  #include <unistd.h>
#endif


/**
* @brief Set terminal text color (foreground only).
* @code
* CPG_term::set_color(CPG_term::Color::White);
* @endcode
* @param color The color to set for the terminal text.
* @return None.
 */
void CPG_term_set_color(CPG_TermColor color) {
  switch (color) {
        case CPG_TERM_COLOR_BLACK:    printf("\033[30m"); break;
        case CPG_TERM_COLOR_RED:      printf("\033[31m"); break;
        case CPG_TERM_COLOR_GREEN:    printf("\033[32m"); break;
        case CPG_TERM_COLOR_YELLOW:   printf("\033[33m"); break;
        case CPG_TERM_COLOR_BLUE:     printf("\033[34m"); break;
        case CPG_TERM_COLOR_MAGENTA:  printf("\033[35m"); break;
        case CPG_TERM_COLOR_CYAN:     printf("\033[36m"); break;
        case CPG_TERM_COLOR_GRAY:     printf("\033[90m"); break;
        case CPG_TERM_COLOR_WHITE:    printf("\033[37m"); break;
        case CPG_TERM_COLOR_LGRED:    printf("\033[91m"); break;
        case CPG_TERM_COLOR_LGGREEN:  printf("\033[92m"); break;
        case CPG_TERM_COLOR_LYELLOW:  printf("\033[93m"); break;
        case CPG_TERM_COLOR_LBLUE:    printf("\033[94m"); break;
        case CPG_TERM_COLOR_LMAGENTA: printf("\033[95m"); break;
        case CPG_TERM_COLOR_LCYAN:    printf("\033[96m"); break;
        case CPG_TERM_COLOR_LGRAY:    printf("\033[97m"); break;
        case CPG_TERM_COLOR_DEFAULT:  printf("\033[0m");  break;
  }
}

/**
 * @brief Reset terminal text color to default.
 * @code
 * CPG_term::reset_color();
 * @endcode
 * @return None.
 */
void CPG_term_reset_color(void) {
  printf("\033[0m");
}

/**
 * @brief Clear the terminal screen.
 * @code
 * CPG_term::clear();
 * @endcode
 * @return None.
 */
void CPG_term_clearsc(void) {
  printf("\033[2J\033[H");
}

/**
 * @brief Get the size of the terminal (width and height).
 * @code
 * int cols, rows;
 * CPG_term_get_size(&cols, &rows);
 * printf("Terminal size: %d cols x %d rows\n", cols, rows);
 * @endcode
 * @return A pair containing the width (columns) and height (rows) of the terminal.
 */
void CPG_term_get_size(int* out_cols, int* out_rows) {
	if (out_cols==NULL||out_rows==NULL){
		return;
	}
  #if defined(_WIN32)
      CONSOLE_SCREEN_BUFFER_INFO csbi;
      if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
				*out_cols = csbi.srWindow.Right - scbi.srWindow.Left+1;
				*out_rows = csbi.srWindow.Bottom - scbi.srWindow.Top+1;
      } else {
				*out_cols = 80;
				*out_rows = 24;
			}
  #else
			
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0) {
        *out_cols = ws.ws_col;
        *out_rows = ws.ws_row;
    } else {
        *out_cols = 80;
        *out_rows = 24;
    }
    
  #endif
}
