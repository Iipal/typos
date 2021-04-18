#include "typos.h"

void colouring() {
  if (has_colors()) {
    if (start_color() == OK) {
      colorsize_update_pair(TYPOS_COLOR_OK, COLOR_GREEN, COLOR_BLACK);
      colorsize_update_pair(TYPOS_COLOR_WARN, COLOR_YELLOW, COLOR_BLACK);
      colorsize_update_pair(TYPOS_COLOR_ERROR, COLOR_RED, COLOR_BLACK);
      colorsize_update_pair(TYPOS_COLOR_INFO, COLOR_MAGENTA, COLOR_BLACK);
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

  curs_set(0);
  noecho();

  int input = 0;
  bool is_input_ok = true;

  typing_t test_text = typing_init_text();

  for (size_t i = 0; test_text[i]; i++) {
    const char *current_string = test_text[i]->string;
    colorize_printw(TYPOS_COLOR_DEFAULT, "%s ", current_string);
    if (!test_text[i + 1]) {
      colorize_printw(TYPOS_COLOR_DEFAULT, "\n");
    }
  }

  const size_t input_line = 1;
  const size_t info_line = 3;

  for (;;) {
    typing_word_t *current_word = typing_get_current_word();
    const char *current_str = current_word ? typing_get_current_string() : NULL;
    const char current_ch = current_word ? typing_get_current_char() : 0;
    const size_t current_ch_pos =
        current_word ? typing_get_current_ch_pos() : 0;

    if (!current_word) {
      colorize_mvprintwe(TYPOS_COLOR_INFO, input_line, 0, "end of words");
    } else if (!current_ch) {
      colorize_mvprintwe(TYPOS_COLOR_INFO, input_line, 0, "spacebar");
    } else {
      for (size_t i = 0; current_word->length > i; ++i) {
        colorize_mvaddch(current_word->at_pos_colors[i], input_line, i,
                         current_str[i]);
      }

      colorize_mvprintw(TYPOS_COLOR_DEFAULT, input_line, current_word->length,
                        "%12c", ' ');
    }

    input = getch();
    is_input_ok = false;

    if (input) {
      colorize_mvprintw(TYPOS_COLOR_INFO, input_line, 20,
                        " | last input: %d:'%c'\n", input, input);
    }

    if (input == 127) {
      typing_backspace();
      continue;
    }

    if (current_ch) {
      is_input_ok = (current_ch == input);
      if (is_input_ok) {
        current_word->at_pos_colors[current_ch_pos] = TYPOS_COLOR_OK;
        colorize_mvprintwe(TYPOS_COLOR_OK, info_line, 0, "correct char\n");
      } else {
        current_word->at_pos_colors[current_ch_pos] = TYPOS_COLOR_ERROR;
        colorize_mvprintwe(TYPOS_COLOR_ERROR, info_line, 0, "invalid char\n");
      }
    } else if (!current_ch && input == ' ') {
      is_input_ok = true;
      colorize_mvprintwe(TYPOS_COLOR_OK, info_line, 0, "ok, next word\n");
    } else {
      colorize_mvprintwe(TYPOS_COLOR_WARN, info_line, 0, "WTF\n");
    }

    typing_iterate();
  }

  endwin();
}
