#include <stddef.h>

#include "ares.h"

extern "C" {
#include <ares_dns.h>
#include <ares_version.h>
}

extern "C" {
int ares_addr_callback(void *arg, int status, struct hostent *hostent);
}

extern "C" {
int ares_parse_a_reply(const unsigned char *abuf, int alen,
                       struct hostent **host);
int ares_parse_aaaa_reply(const unsigned char *abuf, int alen,
                          struct hostent **host);
int ares_parse_mx_reply(const unsigned char *abuf, int alen,
                        struct hostent **host);
int ares_parse_ns_reply(const unsigned char *abuf, int alen,
                        struct hostent **host);
int ares_parse_ptr_reply(const unsigned char *abuf, int alen,
                         struct hostent **host);
int ares_parse_srv_reply(const unsigned char *abuf, int alen,
                         struct hostent **host);
int ares_parse_txt_reply(const unsigned char *abuf, int alen,
                         struct hostent **host);
}

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  // Feed the data into each of the ares_parse_*_reply functions.
  ares_addr_callback(data, size, data, size);
  ares_parse_a_reply(data, size, NULL);
  ares_parse_aaaa_reply(data, size, NULL);
  ares_parse_mx_reply(data, size, NULL);
  ares_parse_ns_reply(data, size, NULL);
  ares_parse_ptr_reply(data, size, NULL);
  ares_parse_srv_reply(data, size, NULL);
  ares_parse_txt_reply(data, size, NULL);
  return 0;
}