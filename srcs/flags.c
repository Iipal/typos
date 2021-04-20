#include "typos.h"

#define FLAG_N 'n'
#define FLAG_H 'h'
#define FLAG_T 't'

#define FLAGS_OPT "hn:t:"

#define FLAGS_USAGE "Usage: ./typos [" FLAGS_OPT "]"

#define FLAG_N_DEFAULT 25
#define FLAG_N_MIN 10
#define FLAG_N_MAX 100

#define FLAG_T_DEFAULT 60
#define FLAG_T_MIN 10
#define FLAG_T_MAX 240

#define FLAG_N_DESC                                                            \
  "Number of maximum random words to type.\n"                                  \
  "                Accepts only positive integer in range: 10 - 100; "         \
  "Default: 25."
#define FLAG_T_DESC                                                            \
  "Number of maximum time to type in seconds.\n"                               \
  "                Accepts only positive integer in range: 10 - 240; "         \
  "Default: 60."

#define FLAG_H_DESC                                                            \
  FLAGS_USAGE "\n"                                                             \
              "  -h          : print this message.\n"                          \
              "  -t [seconds]: " FLAG_T_DESC "\n"                              \
              "  -n [number] : " FLAG_N_DESC "\n"

struct s_flags g_flags = {FLAG_N_DEFAULT, FLAG_T_DEFAULT};

static inline void invalid_positive_integer_errx(char flag, int value, int min,
                                                 int max, int def) {
  errx(EXIT_FAILURE,
       "Invalid argument for `%c`.\nGiven argument: `%d`\n"
       "Accepts only positive integer in range: %d - %d; "
       "Default: %d.\n",
       flag, value, min, max, def);
}

static inline ssize_t flag_positive_integer_arg_parse(const char *arg,
                                                      char flag, int min,
                                                      int max, int def) {
  size_t i = 0;
  while (arg[i])
    ++i;
  bool is_ok = !arg[i];

  ssize_t value = -1;
  if (is_ok) {
    int value = atoi(arg);
    is_ok = !(min > value || max < value);
  }

  if (!is_ok) {
    invalid_positive_integer_errx(flag, value, min, max, def);
  }
  return value;
}

inline void flags_parse(int argc, char *argv[]) {
  int c;
  while (-1 != (c = getopt(argc, argv, FLAGS_OPT))) {
    switch (c) {
    case FLAG_T:
      g_flags.max_time = flag_positive_integer_arg_parse(
          optarg, FLAG_T, FLAG_T_MIN, FLAG_T_MAX, FLAG_T_DEFAULT);
      break;

    case FLAG_N:
      g_flags.max_words = flag_positive_integer_arg_parse(
          optarg, FLAG_N, FLAG_N_MIN, FLAG_N_MAX, FLAG_N_DEFAULT);
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
