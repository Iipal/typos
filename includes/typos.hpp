#pragma once

#include <assert.h>
#include <iostream>
#include <memory>
#include <ncurses.h>
#include <signal.h>

#include "Colorize.hpp"
#include "TypingWord.hpp"
#include "Typing.hpp"
#include "Print.hpp"
#include "Timer.hpp"
#include "Stats.hpp"
#include "Flags.hpp"

extern void _Noreturn finish(int);
