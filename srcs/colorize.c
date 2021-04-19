#include "typos.h"

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

const struct s_colorize_pair *g_colorize_pairs[] = {
    [TYPOS_COLOR_DEFAULT] = &(struct s_colorize_pair){__colorize_default_on,
                                                      __colorize_default_off},
    [TYPOS_COLOR_ENABLED] = &(struct s_colorize_pair){__colorize_initted_on,
                                                      __colorize_initted_off}};
typos_color_t g_colorize_pairs_mapper[] = {
    [TYPOS_COLOR_DEFAULT] = TYPOS_COLOR_DEFAULT,
    [TYPOS_COLOR_OK] = TYPOS_COLOR_DEFAULT,
    [TYPOS_COLOR_WARN] = TYPOS_COLOR_DEFAULT,
    [TYPOS_COLOR_ERROR] = TYPOS_COLOR_DEFAULT,
    [TYPOS_COLOR_INFO] = TYPOS_COLOR_DEFAULT,
    [TYPOS_COLOR_INFO_INVERT] = TYPOS_COLOR_DEFAULT};

inline void colorize_init() {
  if (has_colors()) {
    if (start_color() == OK) {
      colorsize_update_pair(TYPOS_COLOR_DEFAULT, COLOR_WHITE, COLOR_BLACK);
      colorsize_update_pair(TYPOS_COLOR_OK, COLOR_GREEN, COLOR_BLACK);
      colorsize_update_pair(TYPOS_COLOR_WARN, COLOR_YELLOW, COLOR_BLACK);
      colorsize_update_pair(TYPOS_COLOR_ERROR, COLOR_RED, COLOR_BLACK);
      colorsize_update_pair(TYPOS_COLOR_INFO, COLOR_CYAN, COLOR_BLACK);
      colorsize_update_pair(TYPOS_COLOR_INFO_INVERT, COLOR_WHITE,
                            COLOR_MAGENTA);
    } else {
      finish(0);
      printf("Cannot start colours\n");
    }
  } else {
    finish(0);
    printf("Cannot start colours\n");
  }
}

inline void colorsize_update_pair(typos_color_t color, int fg, int bg) {
  init_pair(color, fg, bg);
  g_colorize_pairs_mapper[color] = TYPOS_COLOR_ENABLED;
}

inline int __attribute__((format(printf, 2, 3)))
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

inline int colorize_mvaddch(int color, int y, int x, const chtype ch) {
  int out = 0;

  g_colorize_pairs[g_colorize_pairs_mapper[color]]->color_on(color);
  out = mvaddch(y, x, ch);
  g_colorize_pairs[g_colorize_pairs_mapper[color]]->color_off(color);

  return out;
}
