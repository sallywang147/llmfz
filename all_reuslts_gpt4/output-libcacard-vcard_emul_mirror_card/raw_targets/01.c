#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "vcard_emul.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a VReaderStruct with fuzzed data
  struct VReaderStruct vreader;
  size_t consumed = stream.ConsumeData(&vreader, sizeof(vreader));

  // If we didn't consume enough data for a VReaderStruct, return early
  if (consumed != sizeof(vreader)) {
    return 0;
  }

  // Call the function with the fuzzed VReaderStruct
  struct VCardStruct *vcard = vcard_emul_mirror_card(&vreader);

  // Free the returned VCardStruct if it is not null
  if (vcard != nullptr) {
    free(vcard);
  }

  return 0;
}