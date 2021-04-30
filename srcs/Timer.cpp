#include "typos.hpp"

int Timer::_remaining_seconds = Timer::SECONDS_DEFAULT;
int Timer::_elapsed_seconds = 0;

Timer::Timer() {}

void Timer::init(int seconds) {
  if (Timer::SECONDS_MIN <= seconds && Timer::SECONDS_MAX >= seconds) {
    Timer::_remaining_seconds = seconds;
  }
  Timer::_elapsed_seconds = 0;

  struct sigaction act;
  act.sa_handler = Timer::timer_handler;
  act.sa_flags = SA_NOCLDWAIT;
  sigfillset(&act.sa_mask);
  sigdelset(&act.sa_mask, SIGALRM);
  sigdelset(&act.sa_mask, SIGINT);
  sigdelset(&act.sa_mask, SIGKILL);
  sigaction(SIGALRM, &act, NULL);

  struct itimerval val;
  val.it_value.tv_sec = 1;
  val.it_value.tv_usec = 0;
  val.it_interval = val.it_value;
  setitimer(ITIMER_REAL, &val, NULL);
}

int Timer::get_remaining_seconds(void) { return Timer::_remaining_seconds; }
int Timer::get_elapsed_seconds(void) { return Timer::_elapsed_seconds; }

void Timer::timer_handler(int signo) {
  (void)signo;
  if (!Timer::_remaining_seconds) {
    Timer::break_the_words();
    return;
  } else {
    --Timer::_remaining_seconds;
    ++Timer::_elapsed_seconds;
  }

  Print::timer(Timer::_remaining_seconds);

#ifdef TYPOS_DEBUG
  Print::typing_status(*g_Typing);
#endif
}

void Timer::break_the_words(void) {
  const int y = Print::get_stats_y();
  const auto clean_lines = [y]() {
    for (int i = y; y + 16 > i; ++i) { // hardcoded clear of typing stats
      Print::clean_line(i);
    }
    Print::clean_line(Print::get_input_y());
    Print::clean_line(Print::get_input_y() + 1);
  };

  clean_lines();
  Print::stats(g_Typing->get_stats_data());

  int exit_input = 0;
  do {
    exit_input = Typing::get_input();
  } while (
      !(exit_input == Typing::KEY_ESC || exit_input == Typing::KEY_NEW_LINE));

  if (exit_input == Typing::KEY_NEW_LINE && g_Typing) {
    clean_lines();
    g_Typing->reset();

    box(stdscr, 0, 0);
    Print::render_all(*g_Typing);

    Timer::init(Flags::max_time);
  } else {
    finish(0);
  }
}
