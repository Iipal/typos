#ifndef COLORIZE_H
#define COLORIZE_H

#include <ncurses.h>
#include <stdarg.h>

typedef enum e_colorize {
  COLORIZE_START = 0u,
  COLORIZE_DEFAULT = COLORIZE_START,
  COLORIZE_OK,
  COLORIZE_ENABLED = COLORIZE_OK,
  COLORIZE_WARN,
  COLORIZE_ERROR,
  COLORIZE_INFO,
  COLORIZE_INFO_INVERT,
  COLORIZE_END = COLORIZE_INFO_INVERT
} __attribute__((__packed__)) color_t;

struct s_colorize_pair {
  int (*color_on)(color_t);
  int (*color_off)(color_t);
} __attribute__((aligned(__BIGGEST_ALIGNMENT__)));

extern const struct s_colorize_pair *g_colorize_pairs[];
extern color_t g_colorize_pairs_mapper[];
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
extern void colorsize_update_pair(color_t color, int fg, int bg);

extern int __attribute__((format(printf, 2, 3)))
colorize_printw(color_t color, const char *fmt, ...);
extern int colorize_mvaddch(int color, int y, int x, const chtype ch);

#endif /* COLORIZE_H */
