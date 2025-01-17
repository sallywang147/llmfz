#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "planner.h"

extern "C" {
#include "scanner.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  planner_s ego;
  scanner_s sc;
  std::vector<uint8_t> bytes = stream.ConsumeRemainingBytes();
  sc.buffer = bytes.data();
  sc.end = sc.buffer + bytes.size();
  imprt(&ego, &sc);
  return 0;
}