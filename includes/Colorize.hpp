#pragma once
#include "typos.hpp"

namespace Colorize {
typedef enum e_colorize {
  COLORIZE_DEFAULT = 0u,
  COLORIZE_MIN = COLORIZE_DEFAULT,
  COLORIZE_ENABLED,
  COLORIZE_OK = COLORIZE_ENABLED,
  COLORIZE_WARN,
  COLORIZE_ERROR,
  COLORIZE_INFO,
  COLORIZE_INFO_INVERT,
  COLORIZE_END = COLORIZE_INFO_INVERT,
  COLORIZE_MAX
} __attribute__((__packed__)) color_t;

void init_colors(void);

int cvprintw(color_t color, unsigned attrs, const char *fmt, va_list va);
int cprintw(color_t color, unsigned attrs, const char *fmt, ...);
int cmvprintw(color_t color, unsigned attrs, int y, int x, const char *fmt,
              ...);
int cmvaddch(color_t color, unsigned attrs, int y, int x, const chtype ch);

int cvprintw(color_t color, const char *fmt, va_list va);
int cprintw(color_t color, const char *fmt, ...);
int cmvprintw(color_t color, int y, int x, const char *fmt, ...);
int cmvaddch(color_t color, int y, int x, const chtype ch);

#ifdef TYPOS_DEBUG
constexpr const char *clrtostr(color_t color) {
  constexpr const char *strs[COLORIZE_MAX + 1] = {
      "COLORIZE_DEFAULT", "COLORIZE_OK",   "COLORIZE_WARN",
      "COLORIZE_ERROR",   "COLORIZE_INFO", "COLORIZE_INFO_INVERT",
      "INVALID_COLOR"};
  int idx = color;

  if (color < COLORIZE_MIN || color >= COLORIZE_MAX) {
    idx = COLORIZE_MAX;
  }
  return strs[idx];
}
#endif
}; // namespace Colorize
