#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "planner.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct planner_s ego;
  ego.x = stream.ConsumeIntegral<int>();
  ego.y = stream.ConsumeIntegral<int>();
  ego.theta = stream.ConsumeIntegral<int>();
  ego.v = stream.ConsumeIntegral<int>();
  ego.psi = stream.ConsumeIntegral<int>();

  struct scanner_s sc;
  sc.num_readings = stream.ConsumeIntegral<int>();
  sc.readings = new double[sc.num_readings];
  for (int i = 0; i < sc.num_readings; i++) {
    sc.readings[i] = stream.ConsumeIntegral<double>();
  }

  int result = planner(&ego, &sc);  // Fix: Change imprt to planner
  delete[] sc.readings;
  return result;
}