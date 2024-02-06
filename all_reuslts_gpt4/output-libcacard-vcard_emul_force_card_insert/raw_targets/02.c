#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "vcard_emul.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize the vreader struct
  VReaderStruct vreader;
  
  // Consume data for the vreader struct
  vreader.reader_name = stream.ConsumeRandomLengthString().c_str();
  vreader.status = stream.ConsumeIntegral<VReaderStatus>();
  vreader.id = stream.ConsumeIntegral<long>();
  vreader.private_key = stream.ConsumeIntegral<unsigned long>();
  vreader.card = nullptr; // We set this to null as we do not have a card to insert
  
  // Call the function to fuzz
  vcard_emul_force_card_insert(&vreader);
  
  return 0;
}