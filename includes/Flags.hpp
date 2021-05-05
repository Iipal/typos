#pragma once
#include "typos.hpp"

class Flags {
public:
  static void parse(int argc, char * argv[]);

  static unsigned int max_time;
  static unsigned int max_words;
  static std::string  save_path;
  static std::string  stats_fmt;
  static bool         is_auto_save;
  static bool         is_monochrome;
  static bool         is_alphabetic;
  static bool         is_free_mode;

private:
  Flags();
};
