#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

extern "C" {
#include "grpc_transcoding/testing/expect_json_eq.h"
}

namespace google {
namespace grpc {
namespace transcoding {
namespace testing {
namespace {

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  std::string json_a = provider.ConsumeRandomLengthString(100);
  std::string json_b = provider.ConsumeRandomLengthString(100);

  (void)ExpectJsonArrayEq(&json_a, &json_b);

  return 0;
}
}
}
}
}
}