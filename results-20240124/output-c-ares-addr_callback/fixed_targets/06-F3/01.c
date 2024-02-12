#include <stddef.h>

#include "ares.h"

extern "C" {
#include <ares_version.h>
}

// Entrypoint for Clang's libfuzzer
extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  // Feed the data into each of the ares_parse_*_reply functions.
  ares_addrttl_callback callback = addr_callback;
  ares_parse_a_reply(data, size, NULL, NULL, NULL);
  ares_parse_aaaa_reply(data, size, NULL, NULL, NULL);
  ares_parse_ns_reply(data, size, NULL);
  ares_parse_srv_reply(data, size, NULL);
  ares_parse_mx_reply(data, size, NULL);
  ares_parse_txt_reply(data, size, NULL);
  ares_parse_soa_reply(data, size, NULL);
  ares_parse_naptr_reply(data, size, NULL);
  ares_parse_caa_reply(data, size, NULL);
  ares_parse_uri_reply(data, size, NULL);

  return 0;
}

void addr_callback(void *arg, int status, int timeouts,
                  struct hostent *host) {
  return;
}