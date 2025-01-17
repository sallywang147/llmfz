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

  std::string json1 = provider.ConsumeRandomLengthString(100);
  std::string json2 = provider.ConsumeRandomLengthString(100);

  // Run the function to compare two JSON arrays.
  ExpectJsonArrayEq(&json1, &json2);

  return 0;
}
}
}
}
}
}