#include <stdint.h>
#include <znc/Client.h>

extern "C" {
#include <libFuzzer/libFuzzer.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);
  CClient client;
  client.ReadLine(input);
  return 0;
}