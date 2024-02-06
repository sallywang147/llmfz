#include "grpc_transcoding/testing/test_common.h"
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

  std::string input1 = provider.ConsumeRandomLengthString(100);
  std::string input2 = provider.ConsumeRandomLengthString(100);

  bool result = ExpectJsonArrayEq(&input1, &input2);
  (void)result;  // Avoid unused variable warning.

  return 0;
}
} // namespace
} // namespace testing
} // namespace transcoding
} // namespace grpc
} // namespace google