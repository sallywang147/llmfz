#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tidy.h"
#include "tidy-int.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Initialize the library
  tidySetErrorBuffer(NULL, NULL);
  tidySetMallocCall([](size_t size) { return malloc(size); });
  tidySetReallocCall([](void* buf, size_t size) { return realloc(buf, size); });
  tidySetFreeCall([](void* buf) { free(buf); });
  tidySetPanicCall([](const char* mssg) { abort(); });

  // Create a new document
  TidyDoc tdoc = tidyCreate();
  if (!tdoc) {
    return 0;
  }

  // Create a temporary file
  FILE* tmpfile = tmpfile();
  if (!tmpfile) {
    tidyRelease(tdoc);
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  auto bytes = provider.ConsumeRemainingBytes<uint8_t>();
  fwrite(bytes.data(), 1, bytes.size(), tmpfile);
  rewind(tmpfile);

  // Replace stdin with the temporary file
  FILE* old_stdin = stdin;
  stdin = tmpfile;

  // Call the function to fuzz
  tidyDocParseStdin(tdoc);

  // Restore stdin
  stdin = old_stdin;

  // Clean up
  fclose(tmpfile);
  tidyRelease(tdoc);

  return 0;
}