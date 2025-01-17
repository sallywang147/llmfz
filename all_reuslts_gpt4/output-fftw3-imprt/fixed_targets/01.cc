#include <fuzzer/FuzzedDataProvider.h>
#include "fftw3.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Define and initialize planner_s and scanner_s
  struct planner_s ego;
  struct scanner_s sc;

  // Consume data for planner_s
  ego.mkplan = stream.ConsumeIntegral<int>();
  ego.mkplan_d = stream.ConsumeIntegral<int>();
  ego.mkplan_f_d = stream.ConsumeIntegral<int>();
  ego.wisdom_state = (enum wisdom_state_e)stream.ConsumeEnum<wisdom_state_e>();
  ego.timelimit = stream.ConsumeFloatingPoint<double>();

  // Consume data for scanner_s
  sc.line = stream.ConsumeIntegral<int>();
  sc.car = stream.ConsumeIntegral<int>();
  sc.str = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, size)).c_str();

  // Call the function to fuzz
  int result = imprt(&ego, &sc);

  return 0;
}