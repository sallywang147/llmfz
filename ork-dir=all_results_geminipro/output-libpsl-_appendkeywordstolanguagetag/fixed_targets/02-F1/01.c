#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" {
#include "unicode/uloc.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  // Allocate some memory for the input and output buffers.
  const size_t kMaxLocaleIdSize = 128;
  const size_t kMaxAppendAtSize = 128;
  char locale_id[kMaxLocaleIdSize];
  char append_at[kMaxAppendAtSize];
  int status;

  // Generate random values for the input parameters.
  provider.ConsumeBytes(locale_id, kMaxLocaleIdSize);
  provider.ConsumeBytes(append_at, kMaxAppendAtSize);
  int capacity = provider.ConsumeIntegralInRange<int>(0, 1024);
  char strict = provider.ConsumeBool() ? 's' : 'S';
  char had_posix = provider.ConsumeBool() ? 'p' : 'P';

  // Call the function under test.
  int result = _appendKeywordsToLanguageTag(locale_id, append_at, capacity, strict, had_posix, &status);

  // Check that the function returned a valid status code.
  if (status != 0) {
    // An error occurred.
    return 0;
  }

  // Check that the output buffer is not empty.
  if (strlen(append_at) == 0) {
    // The function did not append any keywords to the language tag.
    return 0;
  }

  // Check that the output buffer does not contain any invalid characters.
  for (size_t i = 0; i < strlen(append_at); i++) {
    if (!isalnum(append_at[i]) && append_at[i] != '-') {
      // The output buffer contains an invalid character.
      return 0;
    }
  }

  // The function call was successful.
  return 0;
}