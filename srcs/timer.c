#include "typos.h"

int __timer_seconds_counter = TIMER_SECONDS_DEFAULT;

static inline void __timer_stop_typos(void) {
  const char *msg = "YOUR TIMED OUT";

  clear();
  box(stdscr, 0, 0);

  colorize_mvprintwe(COLORIZE_OK, 1, print_line_get_center_x(strlen(msg)), msg);

  int exit_input = 0;
  do {
    exit_input = typing_get_input();
  } while (!(exit_input == TYPING_KEY_SPACE_BAR ||
             exit_input == TYPING_KEY_NEW_LINE));

  finish(0);
}

static void __timer_handler(int signo) {
  (void)signo;
  if (!__timer_seconds_counter) {
    __timer_stop_typos();
    return;
  } else {
    --__timer_seconds_counter;
  }

  print_timer(__timer_seconds_counter);
}

inline void timer_init(int seconds) {
  if (TIMER_SECONDS_MIN <= seconds && TIMER_SECONDS_MAX >= seconds) {
    __timer_seconds_counter = seconds;
    __timer_seconds_counter = 2;
  }

  struct sigaction act;
  act.sa_handler = __timer_handler;
  act.sa_flags = SA_NOCLDWAIT | SA_NODEFER;
  sigemptyset(&act.sa_mask);
  sigaction(SIGALRM, &act, NULL);

  struct itimerval val;
  val.it_value.tv_sec = 1;
  val.it_value.tv_usec = 0;
  val.it_interval = val.it_value;
  setitimer(ITIMER_REAL, &val, NULL);
}
