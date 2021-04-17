#ifndef COLORIZE_H
#define COLORIZE_H

#include <ncurses.h>
#include <stdarg.h>

enum e_colorize {
  TYPOS_COLORS_START = 0,
  TYPOS_COLOR_DEFAULT = TYPOS_COLORS_START,
  TYPOS_COLOR_OK,
  TYPOS_COLOR_WARN,
  TYPOS_COLOR_ERROR,
  TYPOS_COLORS_END = TYPOS_COLOR_ERROR
};

struct s_colorize_pair {
  void (*color_on)(void);
  void (*color_off)(void);
};
static void g_colorize_default_on(void) {}
static void g_colorize_ok_on(void) { attrset(COLOR_PAIR(TYPOS_COLOR_OK)); }
static void g_colorize_warn_on(void) { attrset(COLOR_PAIR(TYPOS_COLOR_WARN)); }
static void g_colorize_error_on(void) {
  attrset(COLOR_PAIR(TYPOS_COLOR_ERROR));
}
static void g_colorize_default_off(void) {}
static void g_colorize_ok_off(void) { attroff(COLOR_PAIR(TYPOS_COLOR_OK)); }
static void g_colorize_warn_off(void) { attroff(COLOR_PAIR(TYPOS_COLOR_WARN)); }
static void g_colorize_error_off(void) {
  attroff(COLOR_PAIR(TYPOS_COLOR_ERROR));
}

static const struct s_colorize_pair *g_colorize_pairs[] = {
    [TYPOS_COLOR_DEFAULT] = &(struct s_colorize_pair){g_colorize_default_on,
                                                      g_colorize_default_off},
    [TYPOS_COLOR_OK] =
        &(struct s_colorize_pair){g_colorize_ok_on, g_colorize_ok_off},
    [TYPOS_COLOR_WARN] =
        &(struct s_colorize_pair){g_colorize_warn_on, g_colorize_warn_off},
    [TYPOS_COLOR_ERROR] =
        &(struct s_colorize_pair){g_colorize_error_on, g_colorize_error_off}};
static enum e_colorize g_colorize_pairs_mapper[] = {
    [TYPOS_COLOR_DEFAULT] = TYPOS_COLOR_DEFAULT,
    [TYPOS_COLOR_OK] = TYPOS_COLOR_DEFAULT,
    [TYPOS_COLOR_WARN] = TYPOS_COLOR_DEFAULT,
    [TYPOS_COLOR_ERROR] = TYPOS_COLOR_DEFAULT};

static inline void g_colorsize_update_pair(enum e_colorize color, int fg,
                                           int bg) {
  init_pair(color, fg, bg);
  g_colorize_pairs_mapper[color] = color;
}

static inline int __attribute__((format(printf, 2, 3)))
g_colorize_printw(enum e_colorize color, const char *fmt, ...) {
  va_list va;
  int out = 0;

  va_start(va, fmt);
  g_colorize_pairs[g_colorize_pairs_mapper[color]]->color_on();
  out = vw_printw(stdscr, fmt, va);
  g_colorize_pairs[g_colorize_pairs_mapper[color]]->color_off();
  va_end(va);

  return out;
}

static inline int g_colorize_mvaddch(int color, int y, int x, const chtype ch) {
  int out = 0;

  g_colorize_pairs[g_colorize_pairs_mapper[color]]->color_on();
  out = mvaddch(y, x, ch);
  g_colorize_pairs[g_colorize_pairs_mapper[color]]->color_off();

  return out;
}

#endif /* COLORIZE_H */
