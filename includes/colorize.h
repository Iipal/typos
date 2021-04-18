#ifndef COLORIZE_H
#define COLORIZE_H

#include <ncurses.h>
#include <stdarg.h>

enum e_colorize {
  TYPOS_COLORS_START = 0u,
  TYPOS_COLOR_DEFAULT = TYPOS_COLORS_START,
  TYPOS_COLOR_OK,
  TYPOS_COLOR_WARN,
  TYPOS_COLOR_ERROR,
  TYPOS_COLOR_INFO,
  TYPOS_COLORS_END = TYPOS_COLOR_ERROR
} __attribute__((__packed__));

struct s_colorize_pair {
  int (*color_on)(void);
  int (*color_off)(void);
} __attribute__((aligned(__BIGGEST_ALIGNMENT__)));

static int g_colorize_default_on(void) { return 0; }
static int g_colorize_ok_on(void) {
  attrset(COLOR_PAIR(TYPOS_COLOR_OK));
  return 0;
}
static int g_colorize_warn_on(void) {
  attrset(COLOR_PAIR(TYPOS_COLOR_WARN));
  return 0;
}
static int g_colorize_error_on(void) {
  attrset(COLOR_PAIR(TYPOS_COLOR_ERROR));
  return 0;
}
static int g_colorize_info_on(void) {
  attrset(COLOR_PAIR(TYPOS_COLOR_INFO));
  return 0;
}
static int g_colorize_default_off(void) { return 0; }
static int g_colorize_ok_off(void) {
  attroff(COLOR_PAIR(TYPOS_COLOR_OK));
  return 0;
}
static int g_colorize_warn_off(void) {
  attroff(COLOR_PAIR(TYPOS_COLOR_WARN));
  return 0;
}
static int g_colorize_error_off(void) {
  attroff(COLOR_PAIR(TYPOS_COLOR_ERROR));
  return 0;
}
static int g_colorize_info_off(void) {
  attroff(COLOR_PAIR(TYPOS_COLOR_INFO));
  return 0;
}

static const struct s_colorize_pair *g_colorize_pairs[] = {
    [TYPOS_COLOR_DEFAULT] = &(struct s_colorize_pair){g_colorize_default_on,
                                                      g_colorize_default_off},
    [TYPOS_COLOR_OK] =
        &(struct s_colorize_pair){g_colorize_ok_on, g_colorize_ok_off},
    [TYPOS_COLOR_WARN] =
        &(struct s_colorize_pair){g_colorize_warn_on, g_colorize_warn_off},
    [TYPOS_COLOR_ERROR] =
        &(struct s_colorize_pair){g_colorize_error_on, g_colorize_error_off},
    [TYPOS_COLOR_INFO] =
        &(struct s_colorize_pair){g_colorize_info_on, g_colorize_info_off}};
static enum e_colorize g_colorize_pairs_mapper[] = {
    [TYPOS_COLOR_DEFAULT] = TYPOS_COLOR_DEFAULT,
    [TYPOS_COLOR_OK] = TYPOS_COLOR_DEFAULT,
    [TYPOS_COLOR_WARN] = TYPOS_COLOR_DEFAULT,
    [TYPOS_COLOR_ERROR] = TYPOS_COLOR_DEFAULT,
    [TYPOS_COLOR_INFO] = TYPOS_COLOR_DEFAULT};

static inline void colorsize_update_pair(enum e_colorize color, int fg,
                                         int bg) {
  init_pair(color, fg, bg);
  g_colorize_pairs_mapper[color] = color;
}

static inline int __attribute__((format(printf, 2, 3)))
colorize_printw(enum e_colorize color, const char *fmt, ...) {
  va_list va;
  int out = 0;

  va_start(va, fmt);
  g_colorize_pairs[g_colorize_pairs_mapper[color]]->color_on();
  out = vw_printw(stdscr, fmt, va);
  g_colorize_pairs[g_colorize_pairs_mapper[color]]->color_off();
  va_end(va);

  return out;
}

static int __g_colorize_temp_out = 0;

#undef colorize_mvprintw
#define colorize_mvprintw(color, y, x, fmt, ...)                               \
  (g_colorize_pairs[g_colorize_pairs_mapper[(color)]]->color_on(),             \
   (__g_colorize_temp_out = mvprintw((y), (x), fmt, __VA_ARGS__)),             \
   g_colorize_pairs[g_colorize_pairs_mapper[(color)]]->color_off(),            \
   __g_colorize_temp_out)
#undef colorize_mvprintwe
#define colorize_mvprintwe(color, y, x, fmt)                                   \
  (g_colorize_pairs[g_colorize_pairs_mapper[(color)]]->color_on(),             \
   (__g_colorize_temp_out = mvprintw((y), (x), fmt)),                          \
   g_colorize_pairs[g_colorize_pairs_mapper[(color)]]->color_off(),            \
   __g_colorize_temp_out)

static inline int colorize_mvaddch(int color, int y, int x, const chtype ch) {
  int out = 0;

  g_colorize_pairs[g_colorize_pairs_mapper[color]]->color_on();
  out = mvaddch(y, x, ch);
  g_colorize_pairs[g_colorize_pairs_mapper[color]]->color_off();

  return out;
}

#endif /* COLORIZE_H */
