#include "Flags.hpp"
#include <err.h>
#include <getopt.h>

#define FLAG_H 'h'
#define FLAG_W 'w'
#define FLAG_T 't'
#define FLAG_M 'm'
#define FLAG_A 'a'

#define FLAGS_OPT "hw:t:ma"

#define FLAGS_USAGE "Usage: ./typos [" FLAGS_OPT "]"

#define FLAG_W_DEFAULT 42
#define FLAG_W_MIN 10
#define FLAG_W_MAX 150
#define FLAG_W_DESC                                                            \
  "Number of maximum words to type.\n"                                         \
  "                Accepts only positive integer in range: 10 - 150; "         \
  "Default: 42."

#define FLAG_T_DEFAULT Timer::SECONDS_DEFAULT
#define FLAG_T_MIN Timer::SECONDS_MIN
#define FLAG_T_MAX Timer::SECONDS_MAX
#define FLAG_T_DESC                                                            \
  "Number of maximum time to type in seconds.\n"                               \
  "                Accepts only positive integer in range: 10 - 240; "         \
  "Default: 60."

#define FLAG_M_DEFAULT false

#define FLAG_A_DEFAULT false

#define FLAG_H_DESC                                                            \
  FLAGS_USAGE                                                                  \
  "\n"                                                                         \
  "  -h          : print this message.\n"                                      \
  "  -w [number] : " FLAG_W_DESC "\n"                                          \
  "  -t [seconds]: " FLAG_T_DESC "\n"                                          \
  "  -m          : Monochrome mode. Default: false;\n"                         \
  "  -a          : Words sorted in alphabetical order. Default: false;\n"

unsigned int Flags::max_time = FLAG_T_DEFAULT;
unsigned int Flags::max_words = FLAG_W_DEFAULT;
bool Flags::is_monochrome = FLAG_M_DEFAULT;
bool Flags::is_alphabetic = FLAG_A_DEFAULT;

Flags::Flags() {}

static inline ssize_t flag_positive_integer_arg_parse(const char *arg,
                                                      char flag, int min,
                                                      int max, int def) {
  size_t i = 0;
  while (arg[i] && isdigit(arg[i]))
    ++i;
  bool is_ok = !arg[i];

  ssize_t value = -1;
  if (is_ok) {
    value = atoi(arg);
    is_ok = !(min > value || max < value);
  }

  if (!is_ok) {
    errx(EXIT_FAILURE,
         "Invalid argument for `%c`.\nGiven argument: `%ld`\n"
         "Accepts only positive integer in range: %d - %d; "
         "Default: %d.\n",
         flag, value, min, max, def);
  }
  return value;
}

void Flags::parse(int argc, char *argv[]) {
  int c;
  while (-1 != (c = getopt(argc, argv, FLAGS_OPT))) {
    switch (c) {
    case FLAG_W:
      Flags::max_words = flag_positive_integer_arg_parse(
          optarg, FLAG_W, FLAG_W_MIN, FLAG_W_MAX, FLAG_W_DEFAULT);
      break;

    case FLAG_T:
      Flags::max_time = flag_positive_integer_arg_parse(
          optarg, FLAG_T, FLAG_T_MIN, FLAG_T_MAX, FLAG_T_DEFAULT);
      break;

    case FLAG_M:
      Flags::is_monochrome = true;
      break;

    case FLAG_A:
      Flags::is_alphabetic = true;
      break;

    case '?':
      fprintf(stderr, "%s\n", FLAGS_USAGE);
      exit(EXIT_FAILURE);
      break;

    case 'h':
      printf("%s\n", FLAG_H_DESC);
      exit(EXIT_SUCCESS);

    default:
      exit(EXIT_FAILURE);
    }
  }

  int index;
  for (index = optind; index < argc; index++)
    printf("Non-option argument %s\n", argv[index]);
}
