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

  TestZeroCopyInputStream input_stream;
  MessageReader reader(&input_stream);

  while (provider.remaining_bytes() > 0) {
    // Add a few chucks of data to the input stream.
    for (int i = 0; i < provider.ConsumeIntegralInRange(0, 5); i++) {
      input_stream.AddChunk(provider.ConsumeRandomLengthString(100));
    }

    // Run the message reader to get the next message.
    (void)reader.NextMessageAndGrpcFrame();

    // Handle end of input or error due to malformed bytes.
    if (reader.Finished()) {
      return 0;
    }
  }

  std::string error_message;
  JsonArrayTester tester;
  bool closed = tester.TestClosed(reader.GetRawMessage(), &error_message);
  // The error message should be non-empty if the JSON array is not closed.
  if (!closed) {
    assert(!error_message.empty());
  }

  return 0;
}
}
}
}
}
}