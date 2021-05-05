#pragma once

#include <assert.h>
#include <ctime>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>
#include <memory>
#include <ncurses.h>
#include <signal.h>
#include <sstream>
#include <string.h>
#include <string_view>
#include <sys/time.h>
#include <vector>

static inline void _Noreturn finish(int sig) {
  (void)sig;
  if (stdscr) {
    delwin(stdscr);
  }
  endwin();
  exit(EXIT_SUCCESS);
}
