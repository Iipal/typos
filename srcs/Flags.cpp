#include "Flags.hpp"
#include <err.h>
#include <getopt.h>

#define FLAG_h 'h'
#define FLAG_w 'w'
#define FLAG_t 't'
#define FLAG_S 'S'
#define FLAG_o 'o'
#define FLAG_s 's'
#define FLAG_m 'm'
#define FLAG_a 'a'
#define FLAG_f 'f'

#define FLAGS_OPT "hw:t:S:o:smaf"

#define FLAGS_USAGE "Usage: ./typos [" FLAGS_OPT "]"

#define FLAG_w_DEFAULT 42
#define FLAG_w_MIN 10
#define FLAG_w_MAX 150
#define FLAG_w_DESC                                                            \
  "Number of maximum words to type.\n"                                         \
  "                Accepts only positive integer in range: 10 - 150; "         \
  "Default: 42."

#define FLAG_t_DEFAULT Timer::SECONDS_DEFAULT
#define FLAG_t_MIN Timer::SECONDS_MIN
#define FLAG_t_MAX Timer::SECONDS_MAX
#define FLAG_t_DESC                                                            \
  "Number of maximum time to type in seconds.\n"                               \
  "                Accepts only positive integer in range: 10 - 240; "         \
  "Default: 60."

#define FLAG_o_DEFAULT "wrR|tc|TC|aA"
#define FLAG_o_VALID "|wrRtcTCaA"
#define FLAG_o_DESC                                                            \
  "Stats format string.\n\n"                                                   \
  "                Valid format options: `" FLAG_o_VALID "`;\n"                \
  "                Default: `" FLAG_o_DEFAULT "`.\n\n"                         \
  "                Explanation:\n"                                             \
  "                 - `|`: Delimiter.\n"                                       \
  "                 - `w`: Net WPM.\n"                                         \
  "                 - `r`: Gross WPM.\n"                                       \
  "                 - `R`: Net WPM v2.\n"                                      \
  "                 - `t`: Total typed characters.\n"                          \
  "                 - `c`: Characters Per Second.\n"                           \
  "                 - `T`: Corrected typos.\n"                                 \
  "                 - `C`: All typos.\n"                                       \
  "                 - `a`: Accuracy with corrected typos.\n"                   \
  "                 - `A`: Accuracy with all typos.\n"

#define FLAG_S_DEFAULT "./typos.log"
#define FLAG_S_DESC                                                            \
  "Full path to file where your stats will be saved. Default: `./typos.log`;"

#define FLAG_s_DEFAULT false
#define FLAG_s_DESC "Auto-save your stats at the end. Default: false;"

#define FLAG_m_DEFAULT false
#define FLAG_m_DESC "Monochrome mode. Default: false;"

#define FLAG_a_DEFAULT false
#define FLAG_a_DESC "Words sorted in alphabetical order. Default: false;"

#define FLAG_f_DEFAULT false
#define FLAG_f_DESC "Free typing mode. The timer will not start. Default: false"

#define FLAG_H_DESC                                                            \
  FLAGS_USAGE                                                                  \
  "\n"                                                                         \
  "  -h          : print this message.\n"                                      \
  "  -w [number] : " FLAG_w_DESC "\n"                                          \
  "  -t [seconds]: " FLAG_t_DESC "\n"                                          \
  "  -S [path]   : " FLAG_S_DESC "\n"                                          \
  "  -o [fmt_str]: " FLAG_o_DESC "\n"                                          \
  "  -s          : " FLAG_s_DESC "\n"                                          \
  "  -m          : " FLAG_m_DESC "\n"                                          \
  "  -a          : " FLAG_a_DESC "\n"                                          \
  "  -f          : " FLAG_f_DESC "\n"

unsigned int Flags::max_time = FLAG_t_DEFAULT;
unsigned int Flags::max_words = FLAG_w_DEFAULT;
std::string Flags::save_path = FLAG_S_DEFAULT;
std::string Flags::stats_fmt = FLAG_o_DEFAULT;
bool Flags::is_auto_save = FLAG_s_DEFAULT;
bool Flags::is_monochrome = FLAG_m_DEFAULT;
bool Flags::is_alphabetic = FLAG_a_DEFAULT;
bool Flags::is_free_mode = FLAG_f_DEFAULT;

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

static inline std::string flag_stats_fmt_arg_parse(const char *arg) {
  const size_t arg_len = strlen(arg);

  for (size_t i = 0; arg_len > i; ++i) {
    if (!strchr(FLAG_o_VALID, arg[i])) {
      errx(EXIT_FAILURE, "Invalid stats format option: `%c`.\n%s", arg[i],
           FLAG_o_DESC);
    }
  }

  return std::string(arg);
}

void Flags::parse(int argc, char *argv[]) {
  int c;
  while (-1 != (c = getopt(argc, argv, FLAGS_OPT))) {
    switch (c) {
    case FLAG_w:
      Flags::max_words = flag_positive_integer_arg_parse(
          optarg, FLAG_w, FLAG_w_MIN, FLAG_w_MAX, FLAG_w_DEFAULT);
      break;

    case FLAG_t:
      Flags::max_time = flag_positive_integer_arg_parse(
          optarg, FLAG_t, FLAG_t_MIN, FLAG_t_MAX, FLAG_t_DEFAULT);
      break;

    case FLAG_S:
      Flags::save_path = std::string(optarg);
      break;

    case FLAG_o:
      Flags::stats_fmt = flag_stats_fmt_arg_parse(optarg);
      break;

    case FLAG_s:
      Flags::is_auto_save = true;
      break;

    case FLAG_m:
      Flags::is_monochrome = true;
      break;

    case FLAG_a:
      Flags::is_alphabetic = true;
      break;

    case FLAG_f:
      Flags::is_free_mode = true;
      break;

    case '?':
      fprintf(stderr, "%s\n", FLAGS_USAGE);
      exit(EXIT_FAILURE);
      break;

    case 'h':
      printf("%s\n", FLAG_H_DESC);
      exit(EXIT_SUCCESS);

    default:
      printf("%s\n", FLAG_H_DESC);
      exit(EXIT_FAILURE);
    }
  }

  int index;
  for (index = optind; index < argc; index++)
    printf("Non-option argument %s\n", argv[index]);
}
