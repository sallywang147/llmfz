#include "grpc_transcoding/testing/json_array_tester.h"

#include "test_common.h"

#include <cstddef>
#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>
#include <string>

namespace google {
namespace grpc {
namespace transcoding {
namespace testing {
namespace {

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);

  TestZeroCopyInputStream input_stream;
  JsonArrayTester tester(&input_stream);

  while (provider.remaining_bytes() > 0) {
    // Add a few chucks of data to the input stream.
    for (int i = 0; i < provider.ConsumeIntegralInRange(0, 5); i++) {
      input_stream.AddChunk(provider.ConsumeRandomLengthString(100));
    }

    // Run the array tester to get the next message.
    std::string error_message;
    (void)tester.TestClosed(&error_message);

    // Handle end of input or error due to malformed bytes.
    if (tester.Finished()) {
      return 0;
    }
  }

  return 0;
}
} // namespace
} // namespace testing
} // namespace transcoding
} // namespace grpc
} // namespace google