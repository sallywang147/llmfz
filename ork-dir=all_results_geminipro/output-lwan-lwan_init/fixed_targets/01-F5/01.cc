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

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct lwan *l;

  l = lwan_open_for_fuzzing(data, size);
  if (!l)
    return 1;

  lwan_init(l);

  LWAN_NO_DISCARD(lwan_process(l));

  lwan_close(l);

  return 0;
}

int main() {
  return 0;
}