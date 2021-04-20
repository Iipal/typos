#include "typos.h"

const char *__test_strings[] = {
    "trapshooters",   "welled",        "interrelated",  "pipped",
    "overdyes",       "prorogations",  "rigidifying",   "new",
    "ductility",      "grazing",       "unifaces",      "capacitating",
    "orby",           "kernel",        "bumkins",       "moonflowers",
    "chrysoprases",   "explicable",    "nasalised",     "getaways",
    "antimusical",    "vivifies",      "oomiacks",      "kerrias",
    "coulisses",      "cullender",     "playas",        "magnate",
    "sexologic",      "amnic",         "androgynies",   "ruffly",
    "canthal",        "unhairers",     "isotonic",      "aerobats",
    "nonmechanistic", "curabilities",  "needs",         "gemminess",
    "reallots",       "urinate",       "counterplay",   "ravine",
    "animadverts",    "antineutrino",  "disrelishing",  "endopeptidases",
    "confidantes",    "cabbalas",      "deliciousness", "recomputes",
    "laughingly",     "sips",          "fud",           "sufficers",
    "synoptical",     "superior",      "rurban",        "microclines",
    "billet",         "windingly",     "squealers",     "foilsman",
    "gynophobes",     "ptosis",        "backer",        "simioid",
    "perusing",       "ruing",         "neurotoxin",    "phosphene",
    "reschooled",     "lien",          "masting",       "doily",
    "phonemicists",   "unutilized",    "updry",         "unafraid",
    "smugnesses",     "preinterviews", "purfler",       "beglamor",
    "affluently",     "anamneses",     "chaired",       "hardheaded",
    "graybeards",     "drainages",     "stratus",       "emblemizing",
    "bilboes",        "trudgeon",      "flipflopping",  "hands",
    "renails",        "hookup",        "scavenger",     "drawing"};
const size_t __test_strings_length =
    sizeof(__test_strings) / sizeof(*__test_strings);

inline void finish(int sig) {
  (void)sig;
  if (stdscr) {
    delwin(stdscr);
  }
  endwin();
  exit(EXIT_SUCCESS);
}

static inline int welcome_screen(void) {
  const char *msg = "PRESS ANY KEY TO START";
  const int x = (stdscr->_maxx / 2) - (strlen(msg) / 2);

  box(stdscr, 0, 0);
  colorize_mvprintwe(COLORIZE_OK, 1, x, msg);

  int input = typing_get_input();

  timer_init(g_flags.max_time);

  return input;
}

int main(int argc, char *argv[]) {
  flags_parse(argc, argv);

  signal(SIGINT, finish);
  signal(SIGKILL, finish);

  WINDOW *win = NULL;
  assert((win = initscr()));

  colorize_init();

  noecho();

  typing_text_t *test_text =
      typing_text_init(__test_strings, __test_strings_length);

  int input = 0;
  bool is_input_ok = true;
  bool stop = welcome_screen() == TYPING_KEY_ESC;

  while (!stop) {
    box(win, 0, 0);

    typing_word_t *current_word = typing_get_current_word(test_text);
    const char current_ch = typing_get_current_char(test_text);

    print_text(test_text);
    print_text_delimiter();
    print_current_word(current_word, input);

    input = typing_get_input();
    is_input_ok = false;

    if (input == TYPING_KEY_DEL) {
      typing_text_backspace(test_text);
      continue;
    } else if (input == TYPING_KEY_ESC) {
      stop = true;
    } else {
      is_input_ok = typing_validate_input(current_word, input);

#ifdef TYPOS_DEBUG
      print_input_status(current_word ? current_word->string[current_word->pos]
                                      : 0,
                         is_input_ok);
#endif
    }

    if (current_ch || (!current_ch && is_input_ok)) {
      typing_text_iterate(test_text);
    }
  }

  typing_text_free(test_text);

  finish(0);
}
