#pragma once

#include <assert.h>
#include <iostream>
#include <memory>
#include <ncurses.h>
#include <signal.h>

#include "Colorize.hpp"
#include "TypingChar.hpp"
#include "TypingWord.hpp"
#include "TypingStats.hpp"
#include "Typing.hpp"
#include "Print.hpp"
#include "Timer.hpp"
#include "Flags.hpp"

static inline void _Noreturn finish(int sig) {
  (void)sig;
  if (stdscr) {
    delwin(stdscr);
  }
  endwin();
  exit(EXIT_SUCCESS);
}
