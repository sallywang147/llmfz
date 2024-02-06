#include <stddef.h>
#include <netinet/in.h>
#include <fuzzer/FuzzedDataProvider.h>

#include "ares.h"

typedef void (*func_type)(int, const char *, const char *, const char *, void *);

void dummy_callback(int status, const char *node, const char *service, const char *error, void *arg) {
  // Do nothing
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a dummy ares_channeldata
  struct ares_channeldata channeldata;

  // Create a dummy sockaddr
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = stream.ConsumeIntegral<uint16_t>();
  addr.sin_addr.s_addr = stream.ConsumeIntegral<uint32_t>();

  // Consume integers for flags and family
  int flags = stream.ConsumeIntegral<int>();
  int family = stream.ConsumeIntegral<int>();

  // Consume a string for user data
  std::string user_data = stream.ConsumeRemainingBytesAsString();

  // Call ares_getnameinfo with the fuzzed inputs
  ares_getnameinfo(&channeldata, (struct sockaddr *)&addr, flags, family, dummy_callback, (char *)user_data.c_str());

  return 0;
}