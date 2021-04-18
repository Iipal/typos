#include "typos.h"

const char *__test_strings[] = {
    "text",   "test",   "spring", "lmao", "vm", "syka", "vim",  "emacs", "ls",
    "design", "chunks", "alias",  "cd",   "mv", ":3",   "damn", "text",  "test",
};
const size_t __test_strings_length =
    sizeof(__test_strings) / sizeof(*__test_strings);

void colouring() {
  if (has_colors()) {
    if (start_color() == OK) {
      colorsize_update_pair(TYPOS_COLOR_OK, COLOR_GREEN, COLOR_BLACK);
      colorsize_update_pair(TYPOS_COLOR_WARN, COLOR_YELLOW, COLOR_BLACK);
      colorsize_update_pair(TYPOS_COLOR_ERROR, COLOR_RED, COLOR_BLACK);
      colorsize_update_pair(TYPOS_COLOR_INFO, COLOR_MAGENTA, COLOR_BLACK);
      colorsize_update_pair(TYPOS_COLOR_INFO_INVERT, COLOR_WHITE,
                            COLOR_MAGENTA);
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
  bool stop = false;
  const size_t text_line = 0;
  const size_t input_line = 1;
  const size_t info_line = 3;

  typing_text_t *test_text =
      typing_text_init(__test_strings, __test_strings_length);
  typing_word_t **test_words = typing_get_words(test_text);

  while (!stop) {
    typing_word_t *current_word = typing_get_current_word(test_text);
    const size_t current_word_pos = typing_get_current_word_pos(test_text);
    const char *current_str = typing_get_current_string(test_text);
    const char current_ch = typing_get_current_char(test_text);
    const size_t current_ch_pos = typing_get_current_ch_pos(test_text);

    for (size_t i = 0, start_print_pos = 0; test_words[i]; i++) {
      const typing_word_t *word = test_words[i];
      const char *current_string = word->string;
      typos_color_t string_color = TYPOS_COLOR_DEFAULT;

      if (current_word_pos > i) {
        string_color = word->string_color;
      } else if (current_word_pos == i) {
        string_color = TYPOS_COLOR_INFO;
      }

      colorize_mvprintw(string_color, text_line, start_print_pos, "%s ",
                        current_string);
      start_print_pos += word->length + 1;
    }

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

      move(input_line, current_ch_pos);
    }

    input = typing_get_input();
    is_input_ok = false;

    if (input) {
      colorize_mvprintw(TYPOS_COLOR_INFO, input_line, 20,
                        " | last input: %d:'%c'\n", input,
                        input == '\n' ? '|' : input);
    }

    if (input == TYPING_KEY_DEL) {
      typing_text_backspace(test_text);
      continue;
    } else if (input == TYPING_KEY_ESC) {
      stop = true;
    } else {
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

      typing_text_iterate(test_text);
      refresh();
    }
  }

  typing_text_free(test_text);

  curs_set(1);
  endwin();
}
