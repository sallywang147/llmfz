#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "vcard_emul.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the vreader struct
  struct VReaderStruct vreader;

  // Consume data to fill the vreader struct
  vreader.name = stream.ConsumeRandomLengthString().c_str();
  vreader.status = stream.ConsumeIntegral<VReaderStatus>();
  vreader.id = stream.ConsumeIntegral<long>();
  vreader.privateData = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes()).data();

  // Call the target function
  vcard_emul_force_card_insert(&vreader);

  return 0;
}