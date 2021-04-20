#include "typos.h"

int __timer_seconds_counter = TIMER_SECONDS_DEFAULT;

static void __timer_handler(int signo) {
  (void)signo;
  if (!__timer_seconds_counter) {
    // todo app states;
  } else {
    --__timer_seconds_counter;
  }

  print_timer(__timer_seconds_counter);
}

inline void timer_init(int seconds) {
  if (TIMER_SECONDS_MIN <= seconds && TIMER_SECONDS_MAX >= seconds) {
    __timer_seconds_counter = seconds;
  }

  struct sigaction act;
  act.sa_handler = __timer_handler;
  act.sa_flags = SA_NOCLDSTOP | SA_NOCLDWAIT;
  sigemptyset(&act.sa_mask);
  sigaction(SIGALRM, &act, NULL);

  struct itimerval val;
  val.it_value.tv_sec = 1;
  val.it_value.tv_usec = 0;
  val.it_interval = val.it_value;
  setitimer(ITIMER_REAL, &val, NULL);

  print_timer(__timer_seconds_counter);
}
