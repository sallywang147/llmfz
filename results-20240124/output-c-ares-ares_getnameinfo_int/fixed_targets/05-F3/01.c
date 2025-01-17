#include <stddef.h>
#include <ares.h>

extern "C" {
#include <ares_version.h>
}

// Entrypoint for Clang's libfuzzer
extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  // Feed the data into each of the ares_parse_*_reply functions.
  struct ares_channeldata channel;
  struct sockaddr_in addr;
  int len = sizeof(addr);
  ares_callback callback = NULL;
  ares_getnameinfo_int(&channel, (struct sockaddr*)&addr, len, AF_INET,
                       callback, NULL);
  ares_parse_a_reply(&channel, data, size);
  ares_parse_aaaa_reply(&channel, data, size);
  ares_parse_mx_reply(&channel, data, size);
  ares_parse_ns_reply(&channel, data, size);
  ares_parse_cname_reply(&channel, data, size);
  ares_parse_soa_reply(&channel, data, size);
  ares_parse_ptr_reply(&channel, data, size);
  ares_parse_hinfo_reply(&channel, data, size);
  ares_parse_txt_reply(&channel, data, size);
  ares_parse_srv_reply(&channel, data, size);
  ares_parse_naptr_reply(&channel, data, size);
  ares_parse_ds_reply(&channel, data, size);
  ares_parse_sshfp_reply(&channel, data, size);
  ares_parse_rrsig_reply(&channel, data, size);
  ares_parse_nsec_reply(&channel, data, size);
  ares_parse_nsec3_reply(&channel, data, size);
  ares_parse_tkey_reply(&channel, data, size);
  ares_parse_tsig_reply(&channel, data, size);
  ares_parse_ixfr_reply(&channel, data, size);
  ares_parse_axfr_reply(&channel, data, size);
  ares_parse_any_reply(&channel, data, size);

  return 0;
}