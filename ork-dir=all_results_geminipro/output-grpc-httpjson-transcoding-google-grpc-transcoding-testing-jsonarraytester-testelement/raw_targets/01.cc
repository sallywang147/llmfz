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

  JsonArrayTester tester;

  // Add a few chucks of data to the input stream.
  for (int i = 0; i < provider.ConsumeIntegralInRange(0, 5); i++) {
    tester.AddChunk(provider.ConsumeRandomLengthString(100));
  }

  // Run the tester to get the next message.
  std::string element;
  std::string error;
  bool result = tester.TestElement(&element, &error);

  // Handle end of input or error due to malformed bytes.
  if (!result) {
    return 0;
  }

  return 0;
}
} // namespace
} // namespace testing
} // namespace transcoding
} // namespace grpc
} // namespace google