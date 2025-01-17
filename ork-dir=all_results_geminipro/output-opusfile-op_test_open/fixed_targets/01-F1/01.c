#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "opusfile/config.h"
#include "opusfile/include/opusfile.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string file_data = stream.ConsumeRemainingBytesAsString();
  OggOpusFile* of = op_test_open_memory(
      reinterpret_cast<const uint8_t*>(file_data.c_str()), file_data.size());
  if (of == nullptr) {
    return 0;
  }
  op_free(of);
  return 0;
}