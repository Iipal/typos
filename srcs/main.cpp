#include "typos.hpp"

const std::string __test_strings[] = {
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

inline void _Noreturn finish(int sig) {
  (void)sig;
  if (stdscr) {
    delwin(stdscr);
  }
  endwin();
  exit(EXIT_SUCCESS);
}

static inline int welcome_screen(void) {
  const std::string msg = "PRESS ANY KEY TO START";
  const int x = Print::get_center_x(msg.length());

  box(stdscr, 0, 0);
  Colorize::cmvprintw(COLORIZE_OK, 1, x, msg.c_str());

  int input = Typing::get_input();

  Timer::init(Flags::max_time);

  return input;
}

int main(int argc, char *argv[]) {
  signal(SIGINT, finish);
  signal(SIGKILL, finish);

  Flags::parse(argc, argv);

  WINDOW *win = NULL;
  assert((win = initscr()));
  noecho();

  Colorize::init_colors();

  int input = 0;
  bool is_input_ok = true;
  bool stop = welcome_screen() == Typing::KEY_ESC;

  Typing test_typing = Typing(__test_strings, __test_strings_length);
  g_Typing = &test_typing;

  Print::text(test_typing);
  Print::text_delimiter();

  while (!stop) {
    box(win, 0, 0);
    const TypingWord *current_word = test_typing.get_word();
    const char current_ch = current_word->get_char();

    // because of indexing is starting from 0 - +2 means for printing the
    // current word AND for clearing the NEXT word if it's was typed before;
    Print::text(test_typing, test_typing.get_current_word_pos() + 2);
    Print::input_word(current_word);

    input = Typing::get_input();
    is_input_ok = true;

    if (Typing::KEY_ESC == input) {
      break;
    } else if (input == Typing::KEY_DEL) {
      test_typing.backspace();
    } else {
      is_input_ok = test_typing.validate_input(input);

      if (current_ch || (!current_ch && is_input_ok)) {
        test_typing.iterate();
      }
    }

#ifdef TYPOS_DEBUG
    Print::input_status(test_typing, is_input_ok, input);
#endif
  }

  finish(0);
}
