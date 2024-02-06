#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "opusfile/config.h"
#include "opusfile/include/opusfile.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string file_path = stream.ConsumeRemainingBytesAsString();

  int error = 0;
  struct OggOpusFile* file = op_open_file(const_cast<char*>(file_path.c_str()), &error);
  if (file == nullptr) {
    return 0;
  }

  op_free(file);
  return 0;
}