#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "mutt.h"

struct AttachPrivateData {
  int dummy; // Assuming a dummy variable for simplicity
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize AttachPrivateData
  AttachPrivateData apd;
  apd.dummy = stream.ConsumeIntegral<int>();

  // Consume an integer
  int int_arg = stream.ConsumeIntegral<int>();

  // Call the target function
  op_followup(&apd, int_arg);

  return 0;
}