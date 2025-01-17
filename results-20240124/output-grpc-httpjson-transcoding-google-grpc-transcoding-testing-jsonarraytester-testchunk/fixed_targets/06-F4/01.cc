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
    MessageAndGrpcFrame message_and_frame = reader.NextMessageAndGrpcFrame();

    // Handle end of input or error due to malformed bytes.
    if (reader.Finished()) {
      return 0;
    }

    // Test the JSON array.
    std::string json_array;
    std::string error_message;
    bool success = JsonArrayTester::TestChunk(message_and_frame.message, &json_array,
                                           &error_message, false);
    if (!success) {
      // TODO(klempner): Log the error message.
      return 0;
    }
  }

  return 0;
}

// Define the JsonArrayTester class and its TestChunk method here.

}  // namespace
}  // namespace testing
}  // namespace transcoding
}  // namespace grpc
}  // namespace google