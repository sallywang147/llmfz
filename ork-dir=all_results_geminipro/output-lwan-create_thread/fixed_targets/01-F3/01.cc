#include <stdint.h>
#include <stdio.h>
#include <string.h>

extern "C" {
#include "lwan-config.h"
}

#define LWAN_NO_DISCARD(...)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           \
  do {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 \
    __typeof__(__VA_ARGS__) no_discard_ = __VA_ARGS__;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 \
    __asm__ __volatile__("" ::"g"(no_discard_) : "memory");                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            \
  } while (0)

static bool dump(struct config *config, int indent_level) {
  const struct config_line *line;

  if (indent_level > 64)
    return false;

  while ((line = config_read_line(config))) {
    switch (line->type) {
    case CONFIG_LINE_TYPE_LINE:
      LWAN_NO_DISCARD(parse_bool(line->value, false));
      LWAN_NO_DISCARD(parse_long(line->value, 0));
      LWAN_NO_DISCARD(parse_int(line->value, 0));
      LWAN_NO_DISCARD(parse_time_period(line->value, 0));
      break;

    case CONFIG_LINE_TYPE_SECTION_END:
      if (indent_level == 0)
        return false;

      return true;

    case CONFIG_LINE_TYPE_SECTION:
      if (!dump(config, indent_level + 1))
        return false;

      break;
    }
  }

  const char *error = config_last_error(config);

  if (error) {
    printf("Error: %s\n", error);
    return false;
  }

  return true;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct config *config;
  struct lwan *l;
  struct lwan_thread *thread;

  config = config_open_for_fuzzing(data, size);
  if (!config)
    return 1;

  bool dumped = dump(config, 0);

  config_close(config);

  if (!dumped)
    return 0;

  l = lwan_new();
  if (!l)
    return 1;

  thread = lwan_thread_new(l);
  if (!thread) {
    lwan_delete(l);
    return 1;
  }

  create_thread(l, thread);
  join_thread(thread);  // Fix: Join the thread before deleting it.

  lwan_thread_delete(thread);
  lwan_delete(l);

  return 0;
}