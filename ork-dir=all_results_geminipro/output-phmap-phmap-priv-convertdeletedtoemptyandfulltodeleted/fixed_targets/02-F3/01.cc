#include <cstdint>
#include <cstring>
#include <fuzzer/FuzzedDataProvider.h>
#include <phmap/phmap.h>

using namespace phmap::priv;

extern "C" {
#include <string.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  const size_t capacity = fuzzed_data.ConsumeIntegralInRange<size_t>(0, 10000);
  char *ctrl = new char[capacity];
  ConvertDeletedToEmptyAndFullToDeleted(ctrl, capacity);
  delete[] ctrl;
  return 0;
}