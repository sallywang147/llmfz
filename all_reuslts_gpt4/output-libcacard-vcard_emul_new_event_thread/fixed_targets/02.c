#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "vcard_emul.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a SECMODModuleStr object
  SECMODModuleStr module;

  // Fill the object with the fuzzed data
  stream.ConsumeData(&module, sizeof(module));

  // Call the function under test
  vcard_emul_new_event_thread(&module);

  return 0;
}