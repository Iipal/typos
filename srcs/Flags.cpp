#include "Flags.hpp"
#include <err.h>
#include <getopt.h>

#define FLAG_H 'h'
#define FLAG_T 't'
#define FLAG_M 'm'

#define FLAGS_OPT "ht:m"

#define FLAGS_USAGE "Usage: ./typos [" FLAGS_OPT "]"

#define FLAG_M_DEFAULT false

#define FLAG_T_DEFAULT Timer::SECONDS_DEFAULT
#define FLAG_T_MIN Timer::SECONDS_MIN
#define FLAG_T_MAX Timer::SECONDS_MAX

#define FLAG_T_DESC                                                            \
  "Number of maximum time to type in seconds.\n"                               \
  "                Accepts only positive integer in range: 10 - 240; "         \
  "Default: 60."

#define FLAG_H_DESC                                                            \
  FLAGS_USAGE "\n"                                                             \
              "  -h          : print this message.\n"                          \
              "  -m          : Monochrome mode. Disabling all colors.\n"       \
              "  -t [seconds]: " FLAG_T_DESC "\n"

unsigned int Flags::max_time = FLAG_T_DEFAULT;
bool Flags::is_monochrome = FLAG_M_DEFAULT;

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
    case FLAG_T:
      Flags::max_time = flag_positive_integer_arg_parse(
          optarg, FLAG_T, FLAG_T_MIN, FLAG_T_MAX, FLAG_T_DEFAULT);
      break;

    case FLAG_M:
      Flags::is_monochrome = true;
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
