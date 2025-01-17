#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>

#include "message_reader_tester.h"

namespace google {
namespace grpc {
namespace transcoding {
namespace testing {
namespace {

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  JsonArrayTester tester;

  // Add a few chucks of data to the input stream.
  for (int i = 0; i < provider.ConsumeIntegralInRange(0, 5); i++) {
    tester.AddChunk(provider.ConsumeRandomLengthString(100));
  }

  // Run the message reader to get the next message.
  std::string json_element;
  std::string json_error;
  (void)tester.TestElement(&json_element, &json_error);

  // Handle end of input or error due to malformed bytes.
  if (tester.Finished()) {
    return 0;
  }

  return 0;
}
}
}
}
}
}