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

  std::string json_string;
  std::string expected_json_string;
  // Generate a JSON string with a few nested objects and arrays.
  for (int i = 0; i < provider.ConsumeIntegralInRange(0, 5); i++) {
    json_string += provider.ConsumeRandomLengthString(100);
  }

  // Generate an expected JSON string with a few nested objects and arrays.
  for (int i = 0; i < provider.ConsumeIntegralInRange(0, 5); i++) {
    expected_json_string += provider.ConsumeRandomLengthString(100);
  }

  // Call the function to compare the JSON strings.
  ExpectJsonArrayEq(&json_string, &expected_json_string);

  return 0;
}
}
}
}
}
}