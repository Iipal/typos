#include "Colorize.hpp"
#include "Flags.hpp"
#include "Print.hpp"
#include "Timer.hpp"
#include "Typing.hpp"
#include "TypingKeys.hpp"
#include "Words.hpp"
#include "typos.hpp"

using namespace Colorize;

static inline bool welcome_screen(void) {
  const std::string msg = "PRESS ANY KEY TO START";
  const int         x   = Print::get_center_x(msg.length());

  box(stdscr, 0, 0);
  cmvprintw(COLORIZE_OK, 1, x, msg.c_str());

  int input = TypingKeys::get_input();

  if (TypingKeys::KEY_CTRL_D == input || TypingKeys::KEY_CTRL_C == input ||
      TypingKeys::KEY_ESC == input) {
    return true;
  }

  return false;
}

void do_nothing_sig(int sig) { (void)sig; }

int main(int argc, char * argv[]) {
  std::srand(std::time(0));

  signal(SIGINT, finish);
  signal(SIGKILL, finish);

  Flags::parse(argc, argv);

  WINDOW * win = NULL;
  assert((win = initscr()));
  noecho();
  cbreak();
  raw();
  keypad(stdscr, true);

  init_colors();

  if (welcome_screen()) {
    finish(0);
  }

  Typing test_typing(Words::get_words(Flags::max_words), Flags::max_words);
  Timer::init(Flags::max_time, &test_typing);

  test_typing.run();

  endwin();
}
