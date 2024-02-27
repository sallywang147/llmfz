#include <stddef.h>
#include <cstdint>

#include "ares.h"

// Entrypoint for Clang's libfuzzer
extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  // Feed the data into each of the ares_parse_*_reply functions.
  struct hostent *host = NULL;
  struct ares_addrttl info[5];
  int count = 5;
  ares_parse_a_reply(data, size, &host, info, &count);
  if (host) ares_free_hostent(host);

  host = NULL;
  struct ares_addr6ttl info6[5];
  count = 5;
  ares_parse_aaaa_reply(data, size, &host, info6, &count);
  if (host) ares_free_hostent(host);

  host = NULL;
  unsigned char addrv4[4] = {0x10, 0x20, 0x30, 0x40};
  ares_parse_ptr_reply(data, size, addrv4, sizeof(addrv4), AF_INET, &host);
  if (host) ares_free_hostent(host);

  host = NULL;
  ares_parse_ns_reply(data, size, &host);
  if (host) ares_free_hostent(host);

  struct ares_srv_reply* srv = NULL;
  ares_parse_srv_reply(data, size, &srv);
  if (srv) ares_free_data(srv);

  struct ares_mx_reply* mx = NULL;
  ares_parse_mx_reply(data, size, &mx);
  if (mx) ares_free_data(mx);

  struct ares_txt_reply* txt = NULL;
  ares_parse_txt_reply(data, size, &txt);
  if (txt) ares_free_data(txt);

  struct ares_soa_reply* soa = NULL;
  ares_parse_soa_reply(data, size, &soa);
  if (soa) ares_free_data(soa);

  struct ares_naptr_reply* naptr = NULL;
  ares_parse_naptr_reply(data, size, &naptr);
  if (naptr) ares_free_data(naptr);

  struct ares_caa_reply* caa = NULL;
  ares_parse_caa_reply(data, size, &caa);
  if (caa) ares_free_data(caa);

  struct ares_uri_reply* uri = NULL;
  ares_parse_uri_reply(data, size, &uri);
  if (uri) ares_free_data(uri);

  // Call the function to be fuzzed.
  addr_callback(reinterpret_cast<const uint8_t*>(data), size, 0, reinterpret_cast<const uint8_t*>(data), size);

  return 0;
}

// Function to be fuzzed.
extern "C" void addr_callback(const uint8_t* data, size_t size, int type, const uint8_t* addr, size_t addrlen) {
  // Do something with the data.
}