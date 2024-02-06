#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "opusfile/config.h"
#include "opusfile/include/opusfile.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string filename = stream.ConsumeRemainingBytesAsString();

  OggOpusFile* of = op_open_file(filename.c_str(), &stream);
  if (of == nullptr) {
    return 0;
  }

  op_test_open(of);
  op_free(of);
  return 0;
}