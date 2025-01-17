#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#include <ares.h>

extern "C" {
#include <algorithm>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  ares_channel channel;
  int status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    fprintf(stderr, "ares_init() failed: %s\n", ares_strerror(status));
    return 0;
  }
  std::string name = stream.ConsumeRemainingBytesAsString();
  ares_getaddrinfo(&channel, name.c_str(), nullptr, nullptr, nullptr, nullptr);
  ares_destroy(&channel);
  return 0;
}