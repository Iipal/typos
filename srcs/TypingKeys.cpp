#include "TypingKeys.hpp"
#include "Flags.hpp"
#include "Print.hpp"
#include "Timer.hpp"
#include "typos.hpp"

using namespace TypingKeys;

typedef bool (*__key_handler_t)(key_t key, Typing * __tdata);

static auto __kh_default = [](key_t key, Typing * __tdata) constexpr -> bool {
  (void)key;
  (void)__tdata;
  return false;
};

template <typename __mkey, typename __mvalue, std::size_t __msize> struct Map {
  std::array<std::pair<__mkey, __mvalue>, __msize> __mdata;

  [[nodiscard]] constexpr __mvalue at(const __mkey & key) const {
    const auto itr = std::find_if(std::begin(__mdata),
                                  std::end(__mdata),
                                  [&key](const auto & v) { return v.first == key; });

    return itr != std::end(__mdata) ? itr->second : __kh_default;
  }
};

auto __kh_close = [](key_t key, Typing * __tdata) constexpr -> bool {
  (void)key;
  (void)__tdata;
  return true;
};

auto __kh_ctrl_backspace = [](key_t key, Typing * __tdata) constexpr -> bool {
  (void)key;
  __tdata->reset_word();
  return false;
};
auto __kh_reset_test = [](key_t key, Typing * __tdata) -> bool {
  (void)key;
  __tdata->reset();
  __tdata->reset_stats();
  Timer::reset_timer(Flags::max_time);
  Print::render_all(__tdata);
  return false;
};
auto __kh_reset_test_words = [](key_t key, Typing * __tdata) -> bool {
  __tdata->new_words();
  return __kh_reset_test(key, __tdata);
};

auto __kh_printable = [](key_t key, Typing * __tdata) -> bool {
  const bool         is_input_ok = __tdata->validate_input(key);
  const TypingChar * ch          = __tdata->get_char_at();
  const key_t        _ch         = ch->ch();

  Print::current_char(ch, 0);
  if (_ch || (!_ch && is_input_ok)) {
    __tdata->iterate();
  }

  return false;
};

auto __kh_arrow_left = [](key_t key, Typing * __tdata) -> bool {
  (void)key;
  Print::current_char(__tdata->get_char_at(), 0);
  __tdata->move_to_prev_ch();
  return false;
};
auto __kh_arrow_right = [](key_t key, Typing * __tdata) -> bool {
  (void)key;
  Print::current_char(__tdata->get_char_at(), 0);
  __tdata->move_to_next_ch();
  return false;
};
auto __kh_del = [](key_t key, Typing * __tdata) -> bool {
  (void)key;
  Print::clear_current_char(__tdata->get_char_at());
  __tdata->backspace();
  Print::clear_current_char(__tdata->get_char_at());
  return false;
};

static constexpr auto __key_handlers_arr_size = KEY_MAPPER_MAX;
static constexpr std::array<std::pair<key_t, __key_handler_t>, __key_handlers_arr_size>
    __key_handlers_arr{{
        {KEY_CTRL_C, __kh_close},
        {KEY_CTRL_D, __kh_close},
        {KEY_ESC, __kh_close},

        {
            KEY_CTRL_BACKSPACE,
            __kh_ctrl_backspace,
        },

        {KEY_TAB, __kh_reset_test},
        {KEY_CTRL_R, __kh_reset_test_words},

        {KEY_SPACE, __kh_printable},
        {KEY_EXC_MARK, __kh_printable},
        {KEY_QUOTE, __kh_printable},
        {KEY_NUMBER_SIGN, __kh_printable},
        {KEY_DOLLAR_SIGN, __kh_printable},
        {KEY_PERCENT_SIGN, __kh_printable},
        {KEY_AMPERSAND, __kh_printable},
        {KEY_APOSTROPHE, __kh_printable},
        {KEY_RND_BRACKET_OPEN, __kh_printable},
        {KEY_RND_BRACKET_CLOSE, __kh_printable},
        {KEY_ASTERISK, __kh_printable},
        {KEY_PLUS_SIGN, __kh_printable},
        {KEY_COMMA, __kh_printable},
        {KEY_HYPHEN, __kh_printable},
        {KEY_DOT, __kh_printable},
        {KEY_SLASH, __kh_printable},
        {KEY_ZERO, __kh_printable},
        {KEY_ONE, __kh_printable},
        {KEY_TWO, __kh_printable},
        {KEY_THREE, __kh_printable},
        {KEY_FOUR, __kh_printable},
        {KEY_FIVE, __kh_printable},
        {KEY_SIX, __kh_printable},
        {KEY_SEVEN, __kh_printable},
        {KEY_EIGHT, __kh_printable},
        {KEY_NINE, __kh_printable},
        {KEY_COLON, __kh_printable},
        {KEY_SEMICOLON, __kh_printable},
        {KEY_LESS_SIGN, __kh_printable},
        {KEY_EQUALS_SIGN, __kh_printable},
        {KEY_GREATER_SIGN, __kh_printable},
        {KEY_QUESTION, __kh_printable},
        {KEY_AT_SIGN, __kh_printable},
        {KEY_A, __kh_printable},
        {KEY_B, __kh_printable},
        {KEY_C, __kh_printable},
        {KEY_D, __kh_printable},
        {KEY_E, __kh_printable},
        {KEY_F, __kh_printable},
        {KEY_G, __kh_printable},
        {KEY_H, __kh_printable},
        {KEY_I, __kh_printable},
        {KEY_J, __kh_printable},
        {KEY_K, __kh_printable},
        {KEY_L, __kh_printable},
        {KEY_M, __kh_printable},
        {KEY_N, __kh_printable},
        {KEY_O, __kh_printable},
        {KEY_P, __kh_printable},
        {KEY_Q, __kh_printable},
        {KEY_R, __kh_printable},
        {KEY_S, __kh_printable},
        {KEY_T, __kh_printable},
        {KEY_U, __kh_printable},
        {KEY_V, __kh_printable},
        {KEY_W, __kh_printable},
        {KEY_X, __kh_printable},
        {KEY_Y, __kh_printable},
        {KEY_Z, __kh_printable},
        {KEY_SQR_BRACKET_OPEN, __kh_printable},
        {KEY_BACKS_LASH, __kh_printable},
        {KEY_SQR_BRACKET_CLOSE, __kh_printable},
        {KEY_CARET, __kh_printable},
        {KEY_UNDERSCORE, __kh_printable},
        {KEY_GRAVE, __kh_printable},
        {KEY_a, __kh_printable},
        {KEY_b, __kh_printable},
        {KEY_c, __kh_printable},
        {KEY_d, __kh_printable},
        {KEY_e, __kh_printable},
        {KEY_f, __kh_printable},
        {KEY_g, __kh_printable},
        {KEY_h, __kh_printable},
        {KEY_i, __kh_printable},
        {KEY_j, __kh_printable},
        {KEY_k, __kh_printable},
        {KEY_l, __kh_printable},
        {KEY_m, __kh_printable},
        {KEY_n, __kh_printable},
        {KEY_o, __kh_printable},
        {KEY_p, __kh_printable},
        {KEY_q, __kh_printable},
        {KEY_r, __kh_printable},
        {KEY_s, __kh_printable},
        {KEY_t, __kh_printable},
        {KEY_u, __kh_printable},
        {KEY_v, __kh_printable},
        {KEY_w, __kh_printable},
        {KEY_x, __kh_printable},
        {KEY_y, __kh_printable},
        {KEY_z, __kh_printable},
        {KEY_CRL_BRACKET_OPEN, __kh_printable},
        {KEY_VERTICAL_SLASH, __kh_printable},
        {KEY_CRL_BRACKET_CLOSE, __kh_printable},
        {KEY_TILDE, __kh_printable},

        {KEY_ARROW_LEFT, __kh_arrow_left},
        {KEY_ARROW_RIGHT, __kh_arrow_right},

        {KEY_DEL_CH, __kh_del},
    }};

static constexpr auto __key_handlers =
    Map<key_t, __key_handler_t, __key_handlers_arr_size>{{__key_handlers_arr}};

key_t TypingKeys::get_input(void) {
  key_t ch = 0;

  curs_set(1);

  while ((ch = getch())) {
    if (-1 != ch) {
      break;
    } else {
      napms(16);
    }
  }

  curs_set(0);

  return ch;
}
bool TypingKeys::procced_input(key_t k, void * t) {
  return __key_handlers.at(k)(k, (Typing *)t);
}
