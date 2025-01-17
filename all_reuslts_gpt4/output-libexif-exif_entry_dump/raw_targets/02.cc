#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libexif/exif-entry.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize a _ExifEntry struct with fuzzed data
  _ExifEntry entry;
  entry.tag = stream.ConsumeIntegral<ExifTag>();
  entry.format = stream.ConsumeIntegral<ExifFormat>();
  entry.components = stream.ConsumeIntegral<unsigned long>();
  entry.size = stream.ConsumeIntegral<unsigned int>();
  entry.data = const_cast<unsigned char*>(stream.ConsumeRemainingBytes<unsigned char>().data());

  // Define and initialize the indent parameter
  int indent = stream.ConsumeIntegral<int>();

  // Call the target function
  exif_entry_dump(&entry, indent);

  return 0;
}