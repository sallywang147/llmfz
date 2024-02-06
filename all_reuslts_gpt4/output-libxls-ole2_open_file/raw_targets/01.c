#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ole.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string from the stream
  std::string file_name = stream.ConsumeRandomLengthString();
  char *file = const_cast<char *>(file_name.c_str());

  // Call the function to fuzz
  struct OLE2 *ole2_file = ole2_open_file(file);

  // Close the file if it was successfully opened
  if (ole2_file != NULL) {
    ole2_close_file(ole2_file);
  }

  return 0;
}