#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tidy.h"
#include "tidy-int.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  TidyDoc tdoc = tidyCreate();
  if (tdoc == nullptr) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  std::string str = provider.ConsumeRemainingBytesAsString();
  
  // Create a temporary file and write the data into it.
  FILE* file = tmpfile();
  if (file == nullptr) {
    tidyRelease(tdoc);
    return 0;
  }
  fwrite(str.c_str(), 1, str.size(), file);
  rewind(file);

  // Replace stdin with the temporary file.
  FILE* orig_stdin = stdin;
  stdin = file;

  // Call the target function.
  tidyDocParseStdin((struct _TidyDocImpl *)tdoc);

  // Restore original stdin and close the temporary file.
  stdin = orig_stdin;
  fclose(file);

  tidyRelease(tdoc);
  return 0;
}