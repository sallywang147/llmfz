#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "resip/stack/DialogInfoContents.hxx"
#include "resip/stack/ParseBuffer.hxx"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  // Create a DialogInfoContents object
  resip::DialogInfoContents dialogInfoContents;

  // Create a ParseBuffer object using the fuzzed data
  resip::Data fuzzedData(reinterpret_cast<const char*>(provider.ConsumeRemainingBytes().data()), size);
  resip::ParseBuffer parseBuffer(fuzzedData);

  // Call the target function
  resip::DialogInfoContents::parse(&dialogInfoContents, &parseBuffer);

  return 0;
}