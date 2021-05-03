#include "typos.hpp"

using namespace Colorize;

int __default_on(color_t c, unsigned attrs) {
  attrset(attrs);
  return c;
}
int __default_off(color_t c, unsigned attrs) {
  attroff(attrs);
  return c;
}
int __enabled_on(color_t c, unsigned attrs) {
  return attrset(COLOR_PAIR(c) | attrs);
}
int __enabled_off(color_t c, unsigned attrs) {
  return attroff(COLOR_PAIR(c) | attrs);
}

static const struct {
  int (*color_on)(color_t, unsigned);
  int (*color_off)(color_t, unsigned);
} _colorize_pairs[2][2] = {{{__default_on, __default_off}},
                           {{__enabled_on, __enabled_off}}};

color_t _colorize_pairs_mapper[COLORIZE_MAX] = {
    COLORIZE_DEFAULT, COLORIZE_DEFAULT, COLORIZE_DEFAULT,
    COLORIZE_DEFAULT, COLORIZE_DEFAULT, COLORIZE_DEFAULT};

void _update_pair(color_t color, int fg, int bg) {
  init_pair(color, fg, bg);
  _colorize_pairs_mapper[color] = COLORIZE_ENABLED;
}

int _color_on(color_t c, unsigned attrs) {
  return _colorize_pairs[_colorize_pairs_mapper[c]]->color_on(c, attrs);
}

int _color_off(color_t c, unsigned attrs) {
  return _colorize_pairs[_colorize_pairs_mapper[c]]->color_off(c, attrs);
}

void Colorize::init_colors(void) {
  if (Flags::is_monochrome) {
    return;
  }

  if (has_colors()) {
    if (start_color() == OK) {
      _update_pair(COLORIZE_DEFAULT, COLOR_WHITE, COLOR_BLACK);
      _update_pair(COLORIZE_OK, COLOR_GREEN, COLOR_BLACK);
      _update_pair(COLORIZE_WARN, COLOR_YELLOW, COLOR_BLACK);
      _update_pair(COLORIZE_ERROR, COLOR_RED, COLOR_BLACK);
      _update_pair(COLORIZE_INFO, COLOR_CYAN, COLOR_BLACK);
      _update_pair(COLORIZE_INFO_INVERT, COLOR_WHITE, COLOR_MAGENTA);
    } else {
      std::cerr << "Cannot start colours" << std::endl;
      finish(0);
    }
  } else {
    std::cerr << "Your terminal doesn't support colors" << std::endl;
    finish(0);
  }
}

int Colorize::cvprintw(color_t color, unsigned attrs, const char *fmt,
                       va_list va) {
  int out = 0;

  _color_on(color, attrs);
  out = vw_printw(stdscr, fmt, va);
  _color_off(color, attrs);

  return out;
}

int Colorize::cprintw(color_t color, unsigned attrs, const char *fmt, ...) {
  va_list va;
  int out = 0;

  va_start(va, fmt);
  out = Colorize::cvprintw(color, attrs, fmt, va);
  va_end(va);

  return out;
}

int Colorize::cmvprintw(color_t color, unsigned attrs, int y, int x,
                        const char *fmt, ...) {
  if (stdscr->_maxy <= y) {
    return 0;
  }

  va_list va;
  int out = 0;

  va_start(va, fmt);
  move(y, x);
  out = Colorize::cvprintw(color, attrs, fmt, va);
  va_end(va);

  return out;
}

int Colorize::cmvaddch(color_t color, unsigned attrs, int y, int x,
                       const chtype ch) {
  int out = 0;

  _color_on(color, attrs);
  out = mvaddch(y, x, ch);
  _color_off(color, attrs);

  return out;
}

int Colorize::cvprintw(color_t color, const char *fmt, va_list va) {
  return Colorize::cvprintw(color, 0, fmt, va);
}
int Colorize::cprintw(color_t color, const char *fmt, ...) {
  va_list va;
  int out = 0;

  va_start(va, fmt);
  out = Colorize::cvprintw(color, 0, fmt, va);
  va_end(va);

  return out;
}
int Colorize::cmvprintw(color_t color, int y, int x, const char *fmt, ...) {
  if (stdscr->_maxy <= y) {
    return 0;
  }

  va_list va;
  int out = 0;

  va_start(va, fmt);
  move(y, x);
  out = Colorize::cvprintw(color, fmt, va);
  va_end(va);

  return out;
}
int Colorize::cmvaddch(color_t color, int y, int x, const chtype ch) {
  return Colorize::cmvaddch(color, 0, y, x, ch);
}
