#include <fuzzer/FuzzedDataProvider.h>
#include <plist/plist.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a temporary file to write to
  FILE *temp_file = tmpfile();
  if (!temp_file) {
    return 0;
  }

  // Create a plist string from the input data
  std::string plist_string = stream.ConsumeRemainingBytesAsString();
  char *plist = strdup(plist_string.c_str());

  // Define the format and options
  int format = stream.ConsumeIntegral<int>();
  int options = stream.ConsumeIntegral<int>();

  // Call the function under test
  plist_write_to_stream(plist, temp_file, format, options);

  // Free the allocated memory and close the file
  free(plist);
  fclose(temp_file);

  return 0;
}