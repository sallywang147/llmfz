#include "grpc_transcoding/testing/matchers.h"

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

  // Generate two JSON strings.
  const std::string json1 = provider.ConsumeRandomLengthString(100);
  const std::string json2 = provider.ConsumeRandomLengthString(100);

  // Check if the two JSON strings are equal.
  bool result = ExpectJsonArrayEq(&json1, &json2);

  // Return 0 to indicate success.
  return 0;
}
} // namespace
} // namespace testing
} // namespace transcoding
} // namespace grpc
} // namespace google