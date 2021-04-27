#include "typos.h"

static int __colorize_default_on(color_t c) {
  (void)c;
  return 0;
}
static int __colorize_initted_on(color_t c) {
  attrset(COLOR_PAIR(c));
  return c;
}
static int __colorize_default_off(color_t c) {
  (void)c;
  return 0;
}
static int __colorize_initted_off(color_t c) {
  attroff(COLOR_PAIR(c));
  return c;
}

const struct s_colorize_pair *g_colorize_pairs[] = {
    [COLORIZE_DEFAULT] = &(struct s_colorize_pair){__colorize_default_on,
                                                   __colorize_default_off},
    [COLORIZE_ENABLED] = &(struct s_colorize_pair){__colorize_initted_on,
                                                   __colorize_initted_off}};
color_t g_colorize_pairs_mapper[] = {[COLORIZE_DEFAULT] = COLORIZE_DEFAULT,
                                     [COLORIZE_OK] = COLORIZE_DEFAULT,
                                     [COLORIZE_WARN] = COLORIZE_DEFAULT,
                                     [COLORIZE_ERROR] = COLORIZE_DEFAULT,
                                     [COLORIZE_INFO] = COLORIZE_DEFAULT,
                                     [COLORIZE_INFO_INVERT] = COLORIZE_DEFAULT};

inline void colorize_init() {
  if (has_colors()) {
    if (start_color() == OK) {
      colorize_update_pair(COLORIZE_DEFAULT, COLOR_WHITE, COLOR_BLACK);
      colorize_update_pair(COLORIZE_OK, COLOR_GREEN, COLOR_BLACK);
      colorize_update_pair(COLORIZE_WARN, COLOR_YELLOW, COLOR_BLACK);
      colorize_update_pair(COLORIZE_ERROR, COLOR_RED, COLOR_BLACK);
      colorize_update_pair(COLORIZE_INFO, COLOR_CYAN, COLOR_BLACK);
      colorize_update_pair(COLORIZE_INFO_INVERT, COLOR_WHITE, COLOR_MAGENTA);
    } else {
      printf("Cannot start colours\n");
      finish(0);
    }
  } else {
    printf("Your terminal doesn't support colors\n");
    finish(0);
  }
}

inline void colorize_update_pair(color_t color, int fg, int bg) {
  init_pair(color, fg, bg);
  g_colorize_pairs_mapper[color] = COLORIZE_ENABLED;
}

inline int __attribute__((format(printf, 2, 3)))
colorize_printw(color_t color, const char *fmt, ...) {
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
