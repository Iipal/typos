#ifndef COLORIZE_H
#define COLORIZE_H

#include <ncurses.h>
#include <stdarg.h>

typedef enum e_typos_color {
  TYPOS_COLORS_START = 0u,
  TYPOS_COLOR_DEFAULT = TYPOS_COLORS_START,
  TYPOS_COLOR_OK,
  TYPOS_COLOR_ENABLED = TYPOS_COLOR_OK,
  TYPOS_COLOR_WARN,
  TYPOS_COLOR_ERROR,
  TYPOS_COLOR_INFO,
  TYPOS_COLOR_INFO_INVERT,
  TYPOS_COLORS_END = TYPOS_COLOR_INFO_INVERT
} __attribute__((__packed__)) typos_color_t;

struct s_colorize_pair {
  int (*color_on)(typos_color_t);
  int (*color_off)(typos_color_t);
} __attribute__((aligned(__BIGGEST_ALIGNMENT__)));

static int __colorize_default_on(typos_color_t c) {
  (void)c;
  return 0;
}
static int __colorize_initted_on(typos_color_t c) {
  attrset(COLOR_PAIR(c));
  return c;
}
static int __colorize_default_off(typos_color_t c) {
  (void)c;
  return 0;
}
static int __colorize_initted_off(typos_color_t c) {
  attroff(COLOR_PAIR(c));
  return c;
}

static const struct s_colorize_pair *g_colorize_pairs[] = {
    [TYPOS_COLOR_DEFAULT] = &(struct s_colorize_pair){__colorize_default_on,
                                                      __colorize_default_off},
    [TYPOS_COLOR_ENABLED] = &(struct s_colorize_pair){__colorize_initted_on,
                                                      __colorize_initted_off}};
static typos_color_t g_colorize_pairs_mapper[] = {
    [TYPOS_COLOR_DEFAULT] = TYPOS_COLOR_DEFAULT,
    [TYPOS_COLOR_OK] = TYPOS_COLOR_DEFAULT,
    [TYPOS_COLOR_WARN] = TYPOS_COLOR_DEFAULT,
    [TYPOS_COLOR_ERROR] = TYPOS_COLOR_DEFAULT,
    [TYPOS_COLOR_INFO] = TYPOS_COLOR_DEFAULT,
    [TYPOS_COLOR_INFO_INVERT] = TYPOS_COLOR_DEFAULT};

static inline void colorsize_update_pair(typos_color_t color, int fg, int bg) {
  init_pair(color, fg, bg);
  g_colorize_pairs_mapper[color] = TYPOS_COLOR_ENABLED;
}

static inline int __attribute__((format(printf, 2, 3)))
colorize_printw(typos_color_t color, const char *fmt, ...) {
  va_list va;
  int out = 0;

  va_start(va, fmt);
  g_colorize_pairs[g_colorize_pairs_mapper[color]]->color_on(color);
  out = vw_printw(stdscr, fmt, va);
  g_colorize_pairs[g_colorize_pairs_mapper[color]]->color_off(color);
  va_end(va);

  return out;
}

static int __g_colorize_temp_out = 0;

#undef colorize_mvprintw
#define colorize_mvprintw(color, y, x, fmt, ...)                               \
  (g_colorize_pairs[g_colorize_pairs_mapper[(color)]]->color_on((color)),      \
   (__g_colorize_temp_out = mvprintw((y), (x), fmt, __VA_ARGS__)),             \
   g_colorize_pairs[g_colorize_pairs_mapper[(color)]]->color_off((color)),     \
   __g_colorize_temp_out)
#undef colorize_mvprintwe
#define colorize_mvprintwe(color, y, x, fmt)                                   \
  (g_colorize_pairs[g_colorize_pairs_mapper[(color)]]->color_on((color)),      \
   (__g_colorize_temp_out = mvprintw((y), (x), fmt)),                          \
   g_colorize_pairs[g_colorize_pairs_mapper[(color)]]->color_off((color)),     \
   __g_colorize_temp_out)

static inline int colorize_mvaddch(int color, int y, int x, const chtype ch) {
  int out = 0;

  g_colorize_pairs[g_colorize_pairs_mapper[color]]->color_on(color);
  out = mvaddch(y, x, ch);
  g_colorize_pairs[g_colorize_pairs_mapper[color]]->color_off(color);

  return out;
}

#endif /* COLORIZE_H */
