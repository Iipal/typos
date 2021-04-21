#include "typos.h"

#define STATS_ZERO (struct s_stats){0, 0, 0};

struct s_stats g_stats = STATS_ZERO;

inline void stats_inc_wpm(void) { ++g_stats.words_per_minute; }
inline void stats_inc_cpm(void) { ++g_stats.characters_per_minute; }
inline void stats_inc_typos(void) { ++g_stats.total_miss_typos; }

inline void stats_dec_wpm(void) {
  if (g_stats.words_per_minute)
    --g_stats.words_per_minute;
}
inline void stats_dec_cpm(void) {
  if (g_stats.characters_per_minute)
    --g_stats.characters_per_minute;
}
inline void stats_dec_typos(void) {
  if (g_stats.total_miss_typos)
    --g_stats.total_miss_typos;
}

inline void stats_reset_all(void) { g_stats = STATS_ZERO; }
inline void stats_reset_wpm(void) { g_stats.words_per_minute = 0; }
inline void stats_reset_cpm(void) { g_stats.characters_per_minute = 0; }
inline void stats_reset_typos(void) { g_stats.total_miss_typos = 0; }

inline struct s_stats stats_get_all(void) { return g_stats; }
