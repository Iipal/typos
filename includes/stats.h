#ifndef STATS_H
#define STATS_H

struct s_stats {
  int total_miss_typos;
  int words_per_minute;
  int characters_per_minute;
};

extern void stats_inc_wpm(void);
extern void stats_inc_cpm(void);
extern void stats_inc_typos(void);

extern void stats_dec_wpm(void);
extern void stats_dec_cpm(void);
extern void stats_dec_typos(void);

extern void stats_reset_all(void);
extern void stats_reset_wpm(void);
extern void stats_reset_cpm(void);
extern void stats_reset_typos(void);

extern struct s_stats stats_get_all(void);

#endif /* STATS_H */
