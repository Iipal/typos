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

extern const struct s_colorize_pair *g_colorize_pairs[];
extern typos_color_t g_colorize_pairs_mapper[];
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

extern void colorize_init(void);
extern void colorsize_update_pair(typos_color_t color, int fg, int bg);

extern int __attribute__((format(printf, 2, 3)))
colorize_printw(typos_color_t color, const char *fmt, ...);
extern int colorize_mvaddch(int color, int y, int x, const chtype ch);

#endif /* COLORIZE_H */
