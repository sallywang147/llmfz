 #include "grpc_transcoding/message_reader.h"

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

  std::string expected_json = provider.ConsumeRandomLengthString(100);
  std::string actual_json = provider.ConsumeRandomLengthString(100);

  // Run the function to be fuzzed.
  ExpectJsonArrayEq(&expected_json, &actual_json);

  return 0;
}
}
}
}
}
}