 #include "grpc_transcoding/testing/json_array_tester.h"

#include "test_common.h"

#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>

namespace google {
namespace grpc {
namespace transcoding {
namespace testing {
namespace {

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  JsonArrayTester tester;
  std::string input;
  std::string output;
  bool is_valid;

  while (provider.remaining_bytes() > 0) {
    // Add a few chucks of data to the input string.
    for (int i = 0; i < provider.ConsumeIntegralInRange(0, 5); i++) {
      input += provider.ConsumeRandomLengthString(100);
    }

    // Run the JSON array tester to check if the input is valid.
    is_valid = tester.TestChunk(&input, &output);

    // Handle end of input or error due to malformed bytes.
    if (!is_valid) {
      return 0;
    }
  }

  return 0;
}
}
}
}
}
}