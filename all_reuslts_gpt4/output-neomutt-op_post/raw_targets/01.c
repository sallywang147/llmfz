#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "mutt/mutt.h"

struct IndexSharedData {
  int dummy; // Add real members as per your application
};

struct IndexPrivateData {
  int dummy; // Add real members as per your application
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  IndexSharedData sharedData = {stream.ConsumeIntegral<int>()};
  IndexPrivateData privateData = {stream.ConsumeIntegral<int>()};
  int arg = stream.ConsumeIntegral<int>();

  op_post(&sharedData, &privateData, arg);

  return 0;
}