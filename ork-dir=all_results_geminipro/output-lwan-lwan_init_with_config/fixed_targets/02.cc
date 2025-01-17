#include <stdint.h>
#include <stdio.h>
#include <string.h>

extern "C" {
#include "lwan-config.h"
#include "lwan.h"
}

#define LWAN_NO_DISCARD(...)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           \
  do {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 \
    __typeof__(__VA_ARGS__) no_discard_ = __VA_ARGS__;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 \
    __asm__ __volatile__("" ::"g"(no_discard_) : "memory");                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            \
  } while (0)

static bool parse_bool(const char *value, bool default_value) {
  if (!strcmp(value, "true"))
    return true;
  else if (!strcmp(value, "false"))
    return false;
  else
    return default_value;
}

static long parse_long(const char *value, long default_value) {
  char *endptr;
  long result = strtol(value, &endptr, 10);
  if (*endptr != '\0')
    return default_value;
  else
    return result;
}

static int parse_int(const char *value, int default_value) {
  char *endptr;
  int result = strtol(value, &endptr, 10);
  if (*endptr != '\0')
    return default_value;
  else
    return result;
}

static struct config_time_period parse_time_period(const char *value, struct config_time_period default_value) {
  struct config_time_period result;
  char *endptr;

  result.value = strtol(value, &endptr, 10);
  if (*endptr != '\0')
    return default_value;

  switch (*endptr) {
  case 's':
    result.unit = CONFIG_TIME_PERIOD_UNIT_SECONDS;
    break;
  case 'm':
    result.unit = CONFIG_TIME_PERIOD_UNIT_MINUTES;
    break;
  case 'h':
    result.unit = CONFIG_TIME_PERIOD_UNIT_HOURS;
    break;
  case 'd':
    result.unit = CONFIG_TIME_PERIOD_UNIT_DAYS;
    break;
  default:
    return default_value;
  }

  return result;
}

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
      LWAN_NO_DISCARD(parse_time_period(line->value, (struct config_time_period){0}));
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
  struct lwan_config *lwan_config;

  config = config_open_for_fuzzing(data, size);
  if (!config)
    return 1;

  bool dumped = dump(config, 0);

  lwan_config = lwan_config_new();
  lwan_config_set_config(lwan_config, config);
  l = lwan_new();

  lwan_init_with_config(l, lwan_config);

  config_close(config);
  lwan_config_free(lwan_config);
  lwan_free(l);

  return dumped ? 1 : 0;
}