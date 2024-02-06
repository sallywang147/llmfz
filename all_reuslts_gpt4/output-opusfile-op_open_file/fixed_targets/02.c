#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "opusfile/config.h"
#include "opusfile/include/opusfile.h"
#include <fuzzer/FuzzedDataProvider.h>

// Opusfile fuzzing wrapper to help with automated fuzz testing. It's based on
// https://github.com/xiph/opusfile/blob/master/examples/opusfile_example.c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string str = stream.ConsumeRemainingBytesAsString();
  char *path = const_cast<char*>(str.c_str());

  int error;
  OggOpusFile *of = op_open_file(path, &error);

  if (of != NULL) {
    op_free(of);
  }

  return 0;
}