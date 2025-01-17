#include <fuzzer/FuzzedDataProvider.h>
#include <plist/plist.h>
#include <stdio.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a temporary file to write to.
  FILE *tmpfile = tmpfile();
  if (tmpfile == NULL) {
    return 0;
  }

  // Consume data to create plist, format, and options parameters.
  std::string plist = stream.ConsumeRandomLengthString();
  int format = stream.ConsumeIntegral<int>();
  int options = stream.ConsumeIntegral<int>();

  // Call the function under test.
  plist_write_to_stream(const_cast<char *>(plist.c_str()), tmpfile, format, options);

  // Close the temporary file.
  fclose(tmpfile);

  return 0;
}