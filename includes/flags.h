#ifndef FLAGS_H
#define FLAGS_H

#include <err.h>
#include <stdbool.h>

struct s_flags {
  uint8_t max_words;
  uint8_t max_time;
};

extern struct s_flags g_flags;

extern void flags_parse(int argc, char *argv[]);

#endif /* FLAGS_H */
