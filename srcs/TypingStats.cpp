#include "typos.hpp"

#include <math.h>

TypingStats::TypingStats() : _total_typos(0), _total_characters(0) {}

void TypingStats::inc_chars(void) { ++this->_total_characters; }
void TypingStats::inc_typos(void) { ++this->_total_typos; }

void TypingStats::dec_chars(void) { --this->_total_characters; }
void TypingStats::dec_typos(void) { --this->_total_typos; }

void TypingStats::reset_stats(void) {
  this->reset_chars();
  this->reset_typos();
}
void TypingStats::reset_chars(void) { this->_total_characters = 0; }
void TypingStats::reset_typos(void) { this->_total_typos = 0; }

float TypingStats::get_gross_wpm(void) {
  return ((float)this->_total_characters / 5.0f) /
         ((float)Timer::get_elapsed_seconds() / 60.0f);
}

float TypingStats::get_wpm(void) {
  const float time_elapsed_sec = Timer::get_elapsed_seconds();
  const float time_elapsed_min = (float)time_elapsed_sec / 60.0f;

  const float net_wpm =
      this->get_gross_wpm() - ((float)this->_total_typos / time_elapsed_min);

  return fabs(net_wpm);
}
float TypingStats::get_accuracy(void) {
  float total_chars = this->_total_characters;
  if (!total_chars) {
    total_chars = 1;
  }

  return ((total_chars - this->_total_typos) / total_chars) * 100;
}
int TypingStats::get_chars(void) { return this->_total_characters; }
int TypingStats::get_typos(void) { return this->_total_typos; }
TypingStatsData TypingStats::get_stats_data(void) {
  return {this->get_gross_wpm(), this->get_wpm(), this->get_accuracy(),
          this->get_typos(), this->get_chars()};
}
