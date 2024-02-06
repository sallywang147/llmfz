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

  while (provider.remaining_bytes() > 0) {
    std::string json_string = provider.ConsumeRandomLengthString(100);
    std::string error_message;
    bool is_valid = tester.TestElement(&json_string, &error_message);
    (void)is_valid;
    (void)error_message;
  }

  return 0;
}
} // namespace
} // namespace testing
} // namespace transcoding
} // namespace grpc
} // namespace google