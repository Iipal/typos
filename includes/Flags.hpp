#pragma once
#include "typos.hpp"

class Flags {
public:
  static void parse(int argc, char *argv[]);

  static unsigned int max_time;
  static unsigned int max_words;
  static bool is_monochrome;
  static bool is_alphabetic;

private:
  Flags();
};
