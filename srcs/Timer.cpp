#include "typos.hpp"

#include <string.h>

int Timer::_remaining_seconds = Timer::SECONDS_DEFAULT;
int Timer::_elapsed_seconds = 0;
Typing *Timer::_typing = NULL;

Timer::Timer() {}

void Timer::init(int seconds) { Timer::init(seconds, NULL); }
void Timer::init(int seconds, Typing *typing) {
  if (Timer::SECONDS_MIN <= seconds && Timer::SECONDS_MAX >= seconds) {
    Timer::_remaining_seconds = seconds;
  }
  Timer::_elapsed_seconds = 0;
  if (typing) {
    Timer::_typing = typing;
  }

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
  Print::typing_status(*Timer::_typing);
#endif
}

void Timer::break_the_words(void) {
  const char *msg_saved = "SAVED TO " STATS_SAVE_FILE_NAME;

  const int y = Print::get_stats_y();
  const auto clean_lines = [y]() {
    for (int i = y; y + 16 > i; ++i) { // hardcoded clear of typing stats
      Print::clean_line(i);
    }
    Print::clean_line(Print::get_input_y());
    Print::clean_line(Print::get_input_y() + 1);
  };

  clean_lines();
  Print::stats(Timer::_typing->get_stats_data());

  int ch = 0;
  bool is_saved = false;
  bool stop = false;

  while (!stop) {
    ch = Typing::get_input();

    switch (ch) {
    case Typing::KEY_SLASH: {
      if (!is_saved) {
        TypingStatsDataFmt *fmt =
            TypingStats::get_stats_data_fmt(Timer::_typing->get_stats_data());
        TypingStats::save_stats(fmt);
        delete fmt;

        is_saved = true;
        Colorize::cmvprintw(COLORIZE_INFO_INVERT, Print::get_input_y(),
                            Print::get_center_x(strlen(msg_saved)), msg_saved);
      }

      break;
    }

    case Typing::KEY_NEW_LINE: {
      clean_lines();
      Timer::_typing->reset();
      Timer::_typing->reset_stats();

      box(stdscr, 0, 0);
      Print::render_all(*Timer::_typing);

      Timer::init(Flags::max_time);
      stop = true;
      break;
    }

    case Typing::KEY_ESC:
      finish(0);
      break;

    default:
      break;
    }
  }
}
