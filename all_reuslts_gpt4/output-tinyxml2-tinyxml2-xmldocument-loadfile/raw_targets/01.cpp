#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include "tinyxml2/tinyxml2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract filename as a string
  std::string filename = stream.ConsumeRandomLengthString();
  FILE* file = fopen(filename.c_str(), "wb");
  if (!file) {
    return 0;
  }

  // Write the remaining bytes to file
  std::vector<uint8_t> remaining_bytes = stream.ConsumeRemainingBytes<uint8_t>();
  fwrite(remaining_bytes.data(), 1, remaining_bytes.size(), file);
  fclose(file);

  // Load the file
  tinyxml2::XMLDocument doc;
  doc.LoadFile(filename.c_str());

  // Clean up
  remove(filename.c_str());

  return 0;
}