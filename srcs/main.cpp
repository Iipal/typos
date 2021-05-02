#include "typos.hpp"

static inline bool welcome_screen(void) {
  const std::string msg = "PRESS ANY KEY TO START";
  const int x = Print::get_center_x(msg.length());

  box(stdscr, 0, 0);
  Colorize::cmvprintw(COLORIZE_OK, 1, x, msg.c_str());

  int input = TypingKeys::get_input();

  if (TypingKeys::KEY_CTRL_D == input || TypingKeys::KEY_CTRL_C == input ||
      TypingKeys::KEY_ESC == input) {
    return true;
  }

  return false;
}

void do_nothing_sig(int sig) { (void)sig; }

int main(int argc, char *argv[]) {
  signal(SIGINT, finish);
  signal(SIGKILL, finish);

  Flags::parse(argc, argv);

  WINDOW *win = NULL;
  assert((win = initscr()));
  noecho();
  cbreak();
  raw();
  keypad(stdscr, true);

  Colorize::init_colors();

  int input = 0;
  bool is_input_ok = true;
  bool stop = welcome_screen();
  if (stop) {
    finish(0);
  }

  Typing test_typing(Words::get_words(Flags::max_words), Flags::max_words);
  Timer::init(Flags::max_time, &test_typing);
  Print::render_all(test_typing);

  while (!stop) {
    Print::current_char(test_typing.get_char_at());
    Print::input_word(test_typing);

    input = TypingKeys::get_input();
    is_input_ok = true;

    switch (input) {
    case TypingKeys::KEY_CTRL_BACKSPACE:
      test_typing.reset_word();
      break;

    case TypingKeys::KEY_DEL:
      Print::clear_current_char(test_typing.get_char_at());
      test_typing.backspace();
      Print::clear_current_char(test_typing.get_char_at());
      break;

    case TypingKeys::KEY_CTRL_R:
      test_typing.new_words();
    case TypingKeys::KEY_TAB:
      test_typing.reset();
      test_typing.reset_stats();
      Timer::init(Flags::max_time);
      Print::render_all(test_typing);
      break;

    case TypingKeys::KEY_ARROW_LEFT:
      Print::current_char(test_typing.get_char_at(), 0);
      test_typing.move_to_prev_ch();
      break;

    case TypingKeys::KEY_ARROW_RIGHT:
      Print::current_char(test_typing.get_char_at(), 0);
      test_typing.move_to_next_ch();
      break;

    case TypingKeys::KEY_ESC:
    case TypingKeys::KEY_CTRL_C:
    case TypingKeys::KEY_CTRL_D:
      stop = true;
      break;

    default:
      is_input_ok = test_typing.validate_input(input);

      const TypingChar ch = test_typing.get_char_at();
      Print::current_char(ch, 0);

      const char _ch = ch;
      if (_ch || (!_ch && is_input_ok)) {
        test_typing.iterate();
      }
    }

#ifdef TYPOS_DEBUG
    Print::input_status(test_typing, is_input_ok, input);
#endif
  }

  finish(0);
}
