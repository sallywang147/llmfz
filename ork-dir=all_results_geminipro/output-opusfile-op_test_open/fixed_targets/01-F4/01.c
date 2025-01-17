#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <opus/opus.h>

#include "libfuzzer/libfuzzer_macro.h"

extern "C" {
#include "op_test.h"
}

// This is the function that will be called by the fuzzer.
// It takes a buffer of data as input and returns a size_t indicating
// the number of bytes that were processed.
size_t LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Create an Ogg Opus file object.
  struct OggOpusFile *of = op_test_open(data, size);
  if (of == NULL) {
    return 0;
  }

  // Decode the Opus data.
  int ret = op_test_decode(of);
  if (ret < 0) {
    op_test_close(of);
    return 0;
  }

  // Close the Ogg Opus file object.
  op_test_close(of);

  // Return the number of bytes that were processed.
  return size;
}