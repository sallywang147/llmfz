#include <ares_version.h>
#include <ares.h>

extern "C" {
#include <ares_nameser.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct ares_channeldata channel;
  ares_getnameinfo_int(&channel, (struct sockaddr *)data, size, AF_INET, NULL, NULL);
  return 0;
}