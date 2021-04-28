#include "typos.hpp"

const struct s_colorize_pair Colorize::_colorize_pairs[2][2] = {
    {{Colorize::__default_on, Colorize::__default_off}},
    {{Colorize::__enabled_on, Colorize::__enabled_off}}};
color_t Colorize::_colorize_pairs_mapper[COLORIZE_MAX] = {
    COLORIZE_DEFAULT, COLORIZE_DEFAULT, COLORIZE_DEFAULT,
    COLORIZE_DEFAULT, COLORIZE_DEFAULT, COLORIZE_DEFAULT};

Colorize::Colorize() {}

void Colorize::init_colors(void) {
  if (has_colors()) {
    if (start_color() == OK) {
      Colorize::update_pair(COLORIZE_DEFAULT, COLOR_WHITE, COLOR_BLACK);
      Colorize::update_pair(COLORIZE_OK, COLOR_GREEN, COLOR_BLACK);
      Colorize::update_pair(COLORIZE_WARN, COLOR_YELLOW, COLOR_BLACK);
      Colorize::update_pair(COLORIZE_ERROR, COLOR_RED, COLOR_BLACK);
      Colorize::update_pair(COLORIZE_INFO, COLOR_CYAN, COLOR_BLACK);
      Colorize::update_pair(COLORIZE_INFO_INVERT, COLOR_WHITE, COLOR_MAGENTA);
    } else {
      std::cerr << "Cannot start colours" << std::endl;
      finish(0);
    }
  } else {
    std::cerr << "Your terminal doesn't support colors" << std::endl;
    finish(0);
  }
}

void Colorize::update_pair(color_t color, int fg, int bg) {
  init_pair(color, fg, bg);
  Colorize::_colorize_pairs_mapper[color] = COLORIZE_ENABLED;
}

int Colorize::_color_on(color_t c) {
  return Colorize::_colorize_pairs[Colorize::_colorize_pairs_mapper[c]]
      ->color_on(c);
}

int Colorize::_color_off(color_t c) {
  return Colorize::_colorize_pairs[Colorize::_colorize_pairs_mapper[c]]
      ->color_off(c);
}

int Colorize::cvprintw(color_t color, const char *fmt, va_list va) {
  int out = 0;

  Colorize::_color_on(color);
  out = vw_printw(stdscr, fmt, va);
  Colorize::_color_off(color);

  return out;
}

int Colorize::cprintw(color_t color, const char *fmt, ...) {
  va_list va;
  int out = 0;

  va_start(va, fmt);
  out = Colorize::cvprintw(color, fmt, va);
  va_end(va);

  return out;
}

int Colorize::cmvprintw(color_t color, int y, int x, const char *fmt, ...) {
  va_list va;
  int out = 0;

  va_start(va, fmt);
  move(y, x);
  out = Colorize::cvprintw(color, fmt, va);
  va_end(va);

  return out;
}

int Colorize::cmvaddch(color_t color, int y, int x, const chtype ch) {
  int out = 0;

  Colorize::_color_on(color);
  out = mvaddch(y, x, ch);
  Colorize::_color_off(color);

  return out;
}
