#include "typos.h"

const char *__test_strings[] = {
    "text", "test", "spring", "lmao", "vm", "syka", "vim", "emacs", "ls",
};
const size_t __test_strings_length =
    sizeof(__test_strings) / sizeof(*__test_strings);

inline void finish(int sig) {
  (void)sig;
  delwin(stdscr);
  endwin();
  exit(EXIT_SUCCESS);
}

int main(void) {
  signal(SIGINT, finish);
  signal(SIGKILL, finish);

  WINDOW *win = NULL;
  assert((win = initscr()));

  colorize_init();

  curs_set(0);
  noecho();

  int input = 0;
  bool is_input_ok = true;
  bool stop = false;

  typing_text_t *test_text =
      typing_text_init(__test_strings, __test_strings_length);

  while (!stop) {
    box(win, 0, 0);

    typing_word_t *current_word = typing_get_current_word(test_text);
    const char current_ch = typing_get_current_char(test_text);

    print_text(test_text);
    print_text_delimiter();
    print_current_word(current_word, input);

    input = typing_get_input();
    is_input_ok = false;

    if (input == TYPING_KEY_DEL) {
      typing_text_backspace(test_text);
      continue;
    } else if (input == TYPING_KEY_ESC) {
      stop = true;
    } else {
      is_input_ok = typing_validate_input(current_word, input);

#ifdef TYPOS_DEBUG
      print_input_status(current_word ? current_word->string[current_word->pos]
                                      : 0,
                         is_input_ok);
#endif
    }

    if (current_ch || (!current_ch && is_input_ok)) {
      typing_text_iterate(test_text);
    }
  }

  typing_text_free(test_text);

  curs_set(1);

  finish(0);
}
