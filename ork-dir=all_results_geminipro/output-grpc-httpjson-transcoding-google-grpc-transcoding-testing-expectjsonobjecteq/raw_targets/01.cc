#include "grpc_transcoding/testing/fuzzer_common.h"

#include <cstddef>
#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>
#include <string>

namespace google {
namespace grpc {
namespace transcoding {
namespace testing {

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);

  std::string json_object_1 = provider.ConsumeRandomLengthString();
  std::string json_object_2 = provider.ConsumeRandomLengthString();

  ExpectJsonObjectEq(&json_object_1, &json_object_2);

  return 0;
}
}  // namespace testing
}  // namespace transcoding
}  // namespace grpc
}  // namespace google