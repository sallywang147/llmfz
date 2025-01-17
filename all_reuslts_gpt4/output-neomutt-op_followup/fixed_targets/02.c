#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mutt.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize AttachPrivateData
  struct AttachPrivateData privateData;
  
  // Consume data for the AttachPrivateData
  privateData.fp = nullptr; // File pointer cannot be fuzzed
  privateData.hdr = (HEADER*)stream.ConsumeBytes<uint8_t>(sizeof(HEADER)).data();
  privateData.root = (BODY*)stream.ConsumeBytes<uint8_t>(sizeof(BODY)).data();
  privateData.actx = (ATTACH_CONTEXT*)stream.ConsumeBytes<uint8_t>(sizeof(ATTACH_CONTEXT)).data();
  
  // Consume data for the int parameter
  int num = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  op_followup(&privateData, num);

  return 0;
}