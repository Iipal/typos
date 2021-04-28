#pragma once
#include "typos.hpp"

class Flags {
public:
  static void parse(int argc, char *argv[]);

  static unsigned int max_time;

private:
  Flags();
};
