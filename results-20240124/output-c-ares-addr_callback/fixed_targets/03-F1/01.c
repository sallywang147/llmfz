#include <stddef.h>

#include "ares.h"

extern "C" {
#include "ares_test_fuzz_name.h"
}

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  struct ares_addrttl info[5];
  int count = 5;
  ares_parse_a_reply(data, size, NULL, info, &count);

  for (int i = 0; i < count; i++) {
    addr_callback(info[i].ipaddr, sizeof(info[i].ipaddr), AF_INET, NULL, 0);
  }

  return 0;
}