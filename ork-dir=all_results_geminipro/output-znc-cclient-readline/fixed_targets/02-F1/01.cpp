#include <stdint.h>
#include <znc/Client.h>

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::string input = provider.ConsumeRandomLengthString(size);
  CClient client;
  client.ReadLine(input);
  return 0;
}