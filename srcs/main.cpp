#include "typos.hpp"

static inline int welcome_screen(void) {
  const std::string msg = "PRESS ANY KEY TO START";
  const int x = Print::get_center_x(msg.length());

  box(stdscr, 0, 0);
  Colorize::cmvprintw(COLORIZE_OK, 1, x, msg.c_str());

  int input = Typing::get_input();

  return input;
}

int main(int argc, char *argv[]) {
  signal(SIGINT, finish);
  signal(SIGKILL, finish);

  Flags::parse(argc, argv);

  WINDOW *win = NULL;
  assert((win = initscr()));
  noecho();
  cbreak();
  keypad(stdscr, true);

  Colorize::init_colors();

  int input = 0;
  bool is_input_ok = true;
  bool stop = welcome_screen() == Typing::KEY_ESC;
  if (stop) {
    finish(0);
  }

  Typing test_typing(Words::get_words(Flags::max_words), Flags::max_words);
  Timer::init(Flags::max_time, &test_typing);
  Print::render_all(test_typing);

  while (!stop) {
    const TypingWord *current_word = test_typing.get_word();
    const TypingChar current_char = current_word->get_char_at();
    const chtype current_ch = current_char;

    Print::current_char(current_char);
    Print::input_word(current_word);

    input = Typing::get_input();
    is_input_ok = true;

    switch (input) {
    case Typing::KEY_CTRL_BACKSPACE:
      test_typing.reset_word();
      break;

    case Typing::KEY_ARROW_LEFT:
      Print::current_char(current_char, 0);
      test_typing.move_to_prev_ch();
      break;

    case Typing::KEY_ARROW_RIGHT:
      Print::current_char(current_char, 0);
      test_typing.move_to_next_ch();
      break;

    case Typing::KEY_ESC:
      stop = true;
      break;

    case Typing::KEY_DEL:
      Print::clear_current_char(current_char);
      test_typing.backspace();
      Print::clear_current_char(test_typing.get_word()->get_char_at());
      break;

    default:
      is_input_ok = test_typing.validate_input(input);

      Print::current_char(current_word->get_char_at(), 0);
      if (current_ch || (!current_ch && is_input_ok)) {
        test_typing.iterate();
      }
    }

#ifdef TYPOS_DEBUG
    Print::input_status(test_typing, is_input_ok, input);
#endif
  }

  finish(0);
}
