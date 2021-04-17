#include "typos.h"

void colouring() {
  if (has_colors()) {
    if (start_color() == OK) {
      g_colorsize_update_pair(TYPOS_COLOR_OK, COLOR_GREEN, COLOR_BLACK);
      g_colorsize_update_pair(TYPOS_COLOR_WARN, COLOR_YELLOW, COLOR_BLACK);
      g_colorsize_update_pair(TYPOS_COLOR_ERROR, COLOR_RED, COLOR_BLACK);
    } else {
      addstr("Cannot start colours\n");
    }
  } else {
    addstr("Not colour capable\n");
  }
  refresh();
}

int main(void) {
  initscr();
  colouring();

  g_colorize_printw(TYPOS_COLOR_DEFAULT, "default\n\n");
  g_colorize_printw(TYPOS_COLOR_OK, "correct\n\n");
  g_colorize_printw(TYPOS_COLOR_WARN, "warning\n\n");
  g_colorize_printw(TYPOS_COLOR_ERROR, "error\n");

  curs_set(0);

  const char *text = "testing colorize output by chars";
  for (size_t i = 0; strlen(text) > i; i++) {
    const enum e_colorize color = i % (TYPOS_COLORS_END + 1);
    g_colorize_mvaddch(color, 9, i, text[i]);
  }

  curs_set(1);
  getch();

  endwin();
}
