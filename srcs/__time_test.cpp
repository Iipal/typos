#include "../includes/Colorize.hpp"
#include "../includes/Flags.hpp"
#include "../includes/Print.hpp"
#include "../includes/Timer.hpp"
#include "../includes/TypingKeys.hpp"
#include "../includes/Words.hpp"
#include "../includes/typos.hpp"
#include <chrono>

constexpr auto KEY_CTRL_C         = 0x3;
constexpr auto KEY_CTRL_D         = 0x4;
constexpr auto KEY_CTRL_BACKSPACE = 0x8;
constexpr auto KEY_TAB            = 0x9;
constexpr auto KEY_NEW_LINE       = 0x0A;
constexpr auto KEY_CTRL_R         = 0x12;
constexpr auto KEY_CTRL_S         = 0x13;
constexpr auto KEY_ESC            = 0x1B;

typedef bool (*__key_handler_t)(void * const);
auto __default_close_key_callback = [](void * const __data) constexpr -> bool {
  (void)__data;
  return true;
};
auto __default_key_callback = [](void * const __data) constexpr -> bool {
  (void)__data;
  return false;
};

template <typename __mkey, typename __mvalue, std::size_t __msize> struct Map {
  std::array<std::pair<__mkey, __mvalue>, __msize> __mdata;

  [[nodiscard]] constexpr __mvalue at(const __mkey & key) const {
    const auto itr = std::find_if(std::begin(__mdata),
                                  std::end(__mdata),
                                  [&key](const auto & v) { return v.first == key; });

    if (itr != std::end(__mdata)) {
      return itr->second;
    } else {
      return __default_key_callback;
    }
  }
};

static constexpr std::array<std::pair<__key_t, __key_handler_t>, 2> __key_handlers_arr{
    {{KEY_CTRL_C, __default_close_key_callback},
     {KEY_CTRL_D, __default_close_key_callback}}};

static constexpr auto __key_handlers =
    Map<__key_t, __key_handler_t, __key_handlers_arr.size()>{{__key_handlers_arr}};

static constexpr bool __run_key_handler(__key_t k) { return __key_handlers.at(k)(NULL); }

int main(int argc, char * argv[]) {
  std::srand(std::time(0));

  signal(SIGINT, finish);
  signal(SIGKILL, finish);

  Flags::parse(argc, argv);

  WINDOW * win = NULL;
  assert((win = initscr()));
  noecho();
  cbreak();
  raw();
  keypad(stdscr, true);

  Colorize::init_colors();

  Typing * test_typing = new Typing(Words::get_words(Flags::max_words), Flags::max_words);
  Timer::init(Flags::max_time, test_typing);

  Print::render_all(test_typing);

  TypingKeys::key_t k    = 0;
  bool              stop = false;

  static const constexpr size_t __printable_pseudo_input_size = 95;
  static const constexpr std::array<key_t, __printable_pseudo_input_size>
      __printable_pseudo_input = {
          TypingKeys::KEY_SPACE,
          TypingKeys::KEY_EXC_MARK,
          TypingKeys::KEY_QUOTE,
          TypingKeys::KEY_NUMBER_SIGN,
          TypingKeys::KEY_DOLLAR_SIGN,
          TypingKeys::KEY_PERCENT_SIGN,
          TypingKeys::KEY_AMPERSAND,
          TypingKeys::KEY_APOSTROPHE,
          TypingKeys::KEY_RND_BRACKET_OPEN,
          TypingKeys::KEY_RND_BRACKET_CLOSE,
          TypingKeys::KEY_ASTERISK,
          TypingKeys::KEY_PLUS_SIGN,
          TypingKeys::KEY_COMMA,
          TypingKeys::KEY_HYPHEN,
          TypingKeys::KEY_DOT,
          TypingKeys::KEY_SLASH,
          TypingKeys::KEY_ZERO,
          TypingKeys::KEY_ONE,
          TypingKeys::KEY_TWO,
          TypingKeys::KEY_THREE,
          TypingKeys::KEY_FOUR,
          TypingKeys::KEY_FIVE,
          TypingKeys::KEY_SIX,
          TypingKeys::KEY_SEVEN,
          TypingKeys::KEY_EIGHT,
          TypingKeys::KEY_NINE,
          TypingKeys::KEY_COLON,
          TypingKeys::KEY_SEMICOLON,
          TypingKeys::KEY_LESS_SIGN,
          TypingKeys::KEY_EQUALS_SIGN,
          TypingKeys::KEY_GREATER_SIGN,
          TypingKeys::KEY_QUESTION,
          TypingKeys::KEY_AT_SIGN,
          TypingKeys::KEY_A,
          TypingKeys::KEY_B,
          TypingKeys::KEY_C,
          TypingKeys::KEY_D,
          TypingKeys::KEY_E,
          TypingKeys::KEY_F,
          TypingKeys::KEY_G,
          TypingKeys::KEY_H,
          TypingKeys::KEY_I,
          TypingKeys::KEY_J,
          TypingKeys::KEY_K,
          TypingKeys::KEY_L,
          TypingKeys::KEY_M,
          TypingKeys::KEY_N,
          TypingKeys::KEY_O,
          TypingKeys::KEY_P,
          TypingKeys::KEY_Q,
          TypingKeys::KEY_R,
          TypingKeys::KEY_S,
          TypingKeys::KEY_T,
          TypingKeys::KEY_U,
          TypingKeys::KEY_V,
          TypingKeys::KEY_W,
          TypingKeys::KEY_X,
          TypingKeys::KEY_Y,
          TypingKeys::KEY_Z,
          TypingKeys::KEY_SQR_BRACKET_OPEN,
          TypingKeys::KEY_BACKS_LASH,
          TypingKeys::KEY_SQR_BRACKET_CLOSE,
          TypingKeys::KEY_CARET,
          TypingKeys::KEY_UNDERSCORE,
          TypingKeys::KEY_GRAVE,
          TypingKeys::KEY_a,
          TypingKeys::KEY_b,
          TypingKeys::KEY_c,
          TypingKeys::KEY_d,
          TypingKeys::KEY_e,
          TypingKeys::KEY_f,
          TypingKeys::KEY_g,
          TypingKeys::KEY_h,
          TypingKeys::KEY_i,
          TypingKeys::KEY_j,
          TypingKeys::KEY_k,
          TypingKeys::KEY_l,
          TypingKeys::KEY_m,
          TypingKeys::KEY_n,
          TypingKeys::KEY_o,
          TypingKeys::KEY_p,
          TypingKeys::KEY_q,
          TypingKeys::KEY_r,
          TypingKeys::KEY_s,
          TypingKeys::KEY_t,
          TypingKeys::KEY_u,
          TypingKeys::KEY_v,
          TypingKeys::KEY_w,
          TypingKeys::KEY_x,
          TypingKeys::KEY_y,
          TypingKeys::KEY_z,
          TypingKeys::KEY_CRL_BRACKET_OPEN,
          TypingKeys::KEY_VERTICAL_SLASH,
          TypingKeys::KEY_CRL_BRACKET_CLOSE,
          TypingKeys::KEY_TILDE,
      };
  size_t __printable_pseudo_input_idx = 0;

  auto __get_only_printable_pseudo_input =
      [&__printable_pseudo_input_idx]() -> TypingKeys::key_t {
    key_t __k = __printable_pseudo_input[__printable_pseudo_input_idx++];
    if (__printable_pseudo_input_idx == __printable_pseudo_input_size) {
      __printable_pseudo_input_idx = 0;
    }
    return __k;
  };

#define _TYPING_ITER_MAX 10000000

  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

  for (size_t i = 0; _TYPING_ITER_MAX > i; ++i) {
    k    = __get_only_printable_pseudo_input();
    stop = TypingKeys::procced_input(k, test_typing);
  }

  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

  endwin();
  delete test_typing;

  std::cout << "Time spend on " << _TYPING_ITER_MAX
            << " iteration of only printable characters = " << std::endl
            << "  "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()
            << "[ns]" << std::endl
            << "  "
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
            << "[µs]" << std::endl
            << "  "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
            << "[ms]" << std::endl
            << "  "
            << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count()
            << "[s]" << std::endl;
}
