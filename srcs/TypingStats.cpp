#include "typos.hpp"

#include <math.h>

TypingStats::TypingStats() : _total_typos(0), _total_characters(0) {}

void TypingStats::inc_chars(void) { ++this->_total_characters; }
void TypingStats::inc_typos(void) { ++this->_total_typos; }
void TypingStats::inc_total_typos(void) { ++this->_not_corrected_typos; }

void TypingStats::dec_chars(void) { --this->_total_characters; }
void TypingStats::dec_typos(void) { --this->_total_typos; }

void TypingStats::reset_stats(void) {
  this->reset_chars();
  this->reset_typos();
  this->reset_total_typos();
}
void TypingStats::reset_chars(void) { this->_total_characters = 0; }
void TypingStats::reset_typos(void) { this->_total_typos = 0; }
void TypingStats::reset_total_typos(void) { this->_not_corrected_typos = 0; }

float TypingStats::get_gross_wpm(void) const {
  return ((float)this->_total_characters / 5.0f) /
         ((float)Timer::get_elapsed_seconds() / 60.0f);
}

float TypingStats::_wpm_calc(float typos) const {
  const float time_elapsed_sec = Timer::get_elapsed_seconds();
  const float time_elapsed_min = (float)time_elapsed_sec / 60.0f;

  const float net_wpm = this->get_gross_wpm() - (typos / time_elapsed_min);

  return fabs(net_wpm);
}
float TypingStats::get_wpm(void) const {
  return this->_wpm_calc(this->_total_typos);
}
float TypingStats::get_real_wpm(void) const {
  return this->_wpm_calc(this->_not_corrected_typos);
}

float TypingStats::get_cps(void) const {
  return (float)this->_total_characters / (float)Timer::get_elapsed_seconds();
}

float TypingStats::_acc_calc(float typos) const {
  float total_chars = this->_total_characters;
  if (!total_chars) {
    total_chars = 1;
  }

  return ((total_chars - typos) / total_chars) * 100;
}
float TypingStats::get_accuracy(void) const {
  return this->_acc_calc(this->_total_typos);
}
float TypingStats::get_real_accuracy(void) const {
  return this->_acc_calc(this->_not_corrected_typos);
}

int TypingStats::get_chars(void) const { return this->_total_characters; }
int TypingStats::get_typos(void) const { return this->_total_typos; }
int TypingStats::get_total_typos(void) const {
  return this->_not_corrected_typos;
}

TypingStatsData TypingStats::get_stats_data(void) const {
  return {{this->get_wpm(), this->get_real_wpm(), this->get_gross_wpm()},
          this->get_cps(),
          this->get_accuracy(),
          this->get_real_accuracy(),
          this->get_typos(),
          this->get_total_typos(),
          this->get_chars()};
}
