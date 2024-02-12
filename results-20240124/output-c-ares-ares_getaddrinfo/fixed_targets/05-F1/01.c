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
  ares_init(&channel);
  std::string name = stream.ConsumeRemainingBytesAsString();
  ares_getaddrinfo(&channel, name.c_str(), nullptr, nullptr, nullptr, nullptr);
  ares_destroy(&channel);
  return 0;
}