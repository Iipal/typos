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
  cbreak();
  keypad(stdscr, true);

  Colorize::init_colors();

  int input = 0;
  bool is_input_ok = true;
  bool stop = welcome_screen() == Typing::KEY_ESC;

  Typing test_typing = Typing(__test_strings, __test_strings_length);
  g_Typing = &test_typing;

  Print::text(test_typing);
  Print::text_delimiter();

  while (!stop) {
    const TypingWord *current_word = test_typing.get_word();
    const TypingChar current_char = current_word->get_char_at();
    const chtype current_ch = current_char;

    Print::current_input_char(current_char);
    Print::input_word(current_word);

    input = Typing::get_input();
    is_input_ok = true;

    switch (input) {
    case Typing::KEY_ARROW_LEFT:
      Print::current_input_char(current_char, 0);
      test_typing.move_to_prev_ch();
      break;

    case Typing::KEY_ARROW_RIGHT:
      Print::current_input_char(current_char, 0);
      test_typing.move_to_next_ch();
      break;

    case Typing::KEY_ESC:
      stop = true;
      break;

    case Typing::KEY_DEL:
      Print::clear_current_char(current_char);
      test_typing.backspace();
      Print::clear_current_char(test_typing.get_word()->get_char_at());
      break;

    default:
      is_input_ok = test_typing.validate_input(input);

      Print::current_char(current_word->get_char_at(), input);
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
