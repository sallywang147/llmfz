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
  stream.ConsumeData(&vreader, sizeof(vreader));

  // Call the function with the fuzzed vreader
  struct VCardStruct *vcard = vcard_emul_mirror_card(&vreader);

  // Free the returned VCardStruct
  if (vcard != nullptr) {
    vcard_free(vcard);
  }

  return 0;
}