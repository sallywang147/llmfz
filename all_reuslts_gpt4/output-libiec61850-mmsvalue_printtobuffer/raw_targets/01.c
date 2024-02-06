#include <fuzzer/FuzzedDataProvider.h>

#include "iec61850_server.h"
#include "hal_thread.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Consume 1 byte for MmsValue type
  uint8_t mmsType = stream.ConsumeIntegral<uint8_t>();

  // Create a MmsValue of the specified type
  MmsValue* mmsValue = MmsValue_newIntegerFromInt32(mmsType);

  if (mmsValue == NULL) {
    return 0;
  }

  // Consume the rest of the data for the buffer
  std::string buffer = stream.ConsumeRemainingBytesAsString();

  // Call the function to fuzz
  MmsValue_printToBuffer(mmsValue, buffer.data(), buffer.size());

  // Clean up
  MmsValue_delete(mmsValue);

  return 0;
}