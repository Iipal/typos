#pragma once

#include <assert.h>
#include <iostream>
#include <memory>
#include <ncurses.h>
#include <string.h>
#include <signal.h>
#include <vector>
#include <exception>

#include "Colorize.hpp"

using namespace Colorize;

#include "TypingKeys.hpp"
#include "TypingChar.hpp"
#include "TypingWord.hpp"
#include "TypingStats.hpp"
#include "Typing.hpp"
#include "Print.hpp"
#include "Timer.hpp"
#include "Flags.hpp"
#include "Words.hpp"


static inline void _Noreturn finish(int sig) {
  (void)sig;
  if (stdscr) {
    delwin(stdscr);
  }
  endwin();
  exit(EXIT_SUCCESS);
}