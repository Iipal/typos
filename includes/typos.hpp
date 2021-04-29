#pragma once

#include <assert.h>
#include <iostream>
#include <memory>
#include <ncurses.h>
#include <signal.h>

#include "Colorize.hpp"
#include "TypingWord.hpp"
#include "TypingStats.hpp"
#include "Typing.hpp"
#include "Print.hpp"
#include "Timer.hpp"
#include "Flags.hpp"

extern void _Noreturn finish(int);
