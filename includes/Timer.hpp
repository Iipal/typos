#pragma once

#include <sys/time.h>

class Timer {
public:
  static const int SECONDS_MIN = 10;
  static const int SECONDS_MAX = 240;
  static const int SECONDS_DEFAULT = 60;

  static void init(int seconds);
  static void init(int seconds, Typing *typing);

  static int get_remaining_seconds(void);
  static int get_elapsed_seconds(void);

private:
  Timer();

  static int _remaining_seconds;
  static int _elapsed_seconds;
  static Typing *_typing;

  static void timer_handler(int signo);
  static void break_the_words(void);
};
