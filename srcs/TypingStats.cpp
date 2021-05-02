#include "typos.hpp"

#include <fstream>
#include <iomanip>
#include <math.h>

TypingStats::TypingStats()
    : _total_typos(0), _not_corrected_typos(0), _total_characters(0) {}

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
};

#define STATS_DATA_DELIMITER                                                   \
  {                                                                            \
    "", { "", .0f, COLORIZE_INFO }                                             \
  }

TypingStatsDataFmt *
TypingStats::get_stats_data_fmt(const TypingStatsData &data) {
  TypingStatsDataFmt *out = new TypingStatsDataFmt[13];

  out[0] = {"WPM", {"%-7.2f", data.wpm.net_wpm, COLORIZE_OK}};
  out[1] = {"RAW WPM", {"%-7.2f", data.wpm.gross_wpm, COLORIZE_DEFAULT}};
  out[2] = {"REAL WPM", {"%-7.2f", data.wpm.net_real_wpm, COLORIZE_WARN}};
  out[3] = STATS_DATA_DELIMITER;
  out[4] = {"TYPED", {"%-7.2f", (float)data.characters, COLORIZE_OK}};
  out[5] = {"CPS", {"%-7.2f", data.cps, COLORIZE_OK}};
  out[6] = STATS_DATA_DELIMITER;
  out[7] = {"TYPOS", {"%-7.0f", (float)data.corrected_typos, COLORIZE_WARN}};
  out[8] = {"REAL TYPOS",
            {"%-7.0f", (float)data.not_corrected_typos, COLORIZE_ERROR}};
  out[9] = STATS_DATA_DELIMITER;
  out[10] = {"ACC", {"%-7.2f", data.accuracy, COLORIZE_OK}};
  out[11] = {"REAL ACC", {"%-7.2f", data.real_accuracy, COLORIZE_WARN}};
  out[12] = {NULL, {NULL, .0f, COLORIZE_DEFAULT}};

  return out;
}
void TypingStats::save_stats(const TypingStatsDataFmt *const fmt) {
  std::ofstream file(STATS_SAVE_FILE_NAME, std::ios::app);
  time_t now = time(0);
  tm *_tmp = localtime(&now);

  file << std::endl
       << std::put_time(_tmp, "%a %b %d %H:%M:%S %Y") << " :" << std::endl;

  char fmt_buff[64] = {0};
  char output_buff[128] = {0};

  for (size_t i = 0; fmt[i].first; ++i) {
    snprintf(fmt_buff, sizeof(fmt_buff) - 1, "%%10s | %s", fmt[i].second.fmt);
    snprintf(output_buff, sizeof(output_buff) - 1, fmt_buff, fmt[i].first,
             fmt[i].second.value);

    file << output_buff << std::endl;
  }

  file.close();
}
