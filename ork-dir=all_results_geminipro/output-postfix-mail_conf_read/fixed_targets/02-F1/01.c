#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mail_conf.h"

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::vector<char> input(data, data + size);
  input.push_back('\0');

  // Write the input to a temporary file.
  char* temp_file_name = std::tmpnam(nullptr);
  FILE* temp_file = fopen(temp_file_name, "wb");
  fwrite(input.data(), 1, input.size(), temp_file);
  fclose(temp_file);

  // Read the input from the temporary file.
  mail_conf_read(temp_file_name);

  // Clean up the temporary file.
  remove(temp_file_name);

  return 0;
}