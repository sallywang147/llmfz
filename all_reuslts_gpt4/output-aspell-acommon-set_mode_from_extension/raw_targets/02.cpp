#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "acommon.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  acommon::PosibErr config;
  acommon::Config filename;

  // Consume a string from the stream
  std::string in_str = stream.ConsumeRandomLengthString();
  char *in = const_cast<char*>(in_str.c_str());

  // Consume an integer from the stream
  int integer = stream.ConsumeIntegral<int>();

  // Create a temporary file for fuzzing
  FILE *temp_file = tmpfile();
  if(temp_file == NULL) {
    return 0;
  }

  // Call the function to fuzz
  acommon::set_mode_from_extension(&config, &filename, in, integer, temp_file);

  // Close the temporary file
  fclose(temp_file);

  return 0;
}