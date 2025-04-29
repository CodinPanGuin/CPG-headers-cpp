#pragma once
/**
 * @file CPG-term.h
 * @brief Cross-platform terminal/console utilities (printf style).
 */

#include <stdio.h>
#include <stdbool.h>

#if defined(_WIN32)
  #include <windows.h>
#else
  #include <sys/ioctl.h>
  #include <unistd.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    CPG_TERM_COLOR_DEFAULT,
    CPG_TERM_COLOR_BLACK,
    CPG_TERM_COLOR_RED,
    CPG_TERM_COLOR_GREEN,
    CPG_TERM_COLOR_YELLOW,
    CPG_TERM_COLOR_BLUE,
    CPG_TERM_COLOR_MAGENTA,
    CPG_TERM_COLOR_CYAN,
    CPG_TERM_COLOR_GRAY,
    CPG_TERM_COLOR_WHITE,
    CPG_TERM_COLOR_LGRED,
    CPG_TERM_COLOR_LGGREEN,
    CPG_TERM_COLOR_LYELLOW,
    CPG_TERM_COLOR_LBLUE,
    CPG_TERM_COLOR_LMAGENTA,
    CPG_TERM_COLOR_LCYAN,
    CPG_TERM_COLOR_LGRAY
} CPG_TermColor;

// Function declarations
void CPG_term_set_color(CPG_TermColor color);
void CPG_term_reset_color(void);
void CPG_term_clearsc(void);
void CPG_term_get_size(int* out_cols, int* out_rows);

#ifdef __cplusplus
}
#endif
