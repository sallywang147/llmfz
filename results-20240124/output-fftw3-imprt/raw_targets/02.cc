 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "planner.h"
#include "scanner.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::vector<uint8_t> buffer(stream.ConsumeRemainingBytes());
  struct scanner_s sc;
  scannerInit(&sc, buffer.data(), buffer.size());
  struct planner_s ego;
  imprt(&ego, &sc);
  return 0;
}