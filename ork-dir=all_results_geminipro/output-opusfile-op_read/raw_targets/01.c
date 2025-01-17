#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "opusfile/config.h"
#include "opusfile/include/opusfile.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string file_name = stream.ConsumeRemainingBytesAsString();
  OggOpusFile* of = op_open_file(file_name.c_str(), NULL);
  if (of == NULL) {
    return 0;
  }

  const int buf_size = stream.ConsumeIntegral<int>();
  short* pcm = new short[buf_size];
  int li = 0;
  op_read(of, pcm, buf_size, &li);
  delete[] pcm;
  op_free(of);
  return 0;
}