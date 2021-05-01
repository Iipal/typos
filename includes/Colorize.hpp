#pragma once
#include "typos.hpp"

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

struct s_colorize_pair {
  int (*color_on)(color_t, unsigned);
  int (*color_off)(color_t, unsigned);
};

class Colorize {
public:
  static void init_colors(void);

  static void update_pair(color_t color, int fg, int bg);

  static int cvprintw(color_t color, unsigned attrs, const char *fmt,
                      va_list va);
  static int cprintw(color_t color, unsigned attrs, const char *fmt, ...);
  static int cmvprintw(color_t color, unsigned attrs, int y, int x,
                       const char *fmt, ...);
  static int cmvaddch(color_t color, unsigned attrs, int y, int x,
                      const chtype ch);

  static int cvprintw(color_t color, const char *fmt, va_list va);
  static int cprintw(color_t color, const char *fmt, ...);
  static int cmvprintw(color_t color, int y, int x, const char *fmt, ...);
  static int cmvaddch(color_t color, int y, int x, const chtype ch);

#ifdef TYPOS_DEBUG
  static const char *clrtostr(color_t color);
#endif

private:
  Colorize();

  static int _color_on(color_t c, unsigned attrs);
  static int _color_off(color_t c, unsigned attrs);

  static int __default_on(color_t c, unsigned attrs) {
    attrset(attrs);
    return c;
  }
  static int __default_off(color_t c, unsigned attrs) {
    attroff(attrs);
    return c;
  }
  static int __enabled_on(color_t c, unsigned attrs) {
    return attrset(COLOR_PAIR(c) | attrs);
  }
  static int __enabled_off(color_t c, unsigned attrs) {
    return attroff(COLOR_PAIR(c) | attrs);
  }

  static const struct s_colorize_pair _colorize_pairs[2][2];
  static color_t _colorize_pairs_mapper[COLORIZE_MAX];
};
