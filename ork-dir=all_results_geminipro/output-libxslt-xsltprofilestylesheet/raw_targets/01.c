#include <fuzz.h>

int LLVMFuzzerInitialize(int *argc_p ATTRIBUTE_UNUSED, char ***argv_p ATTRIBUTE_UNUSED) { return xsltFuzzStylesheetInit(); }

int LLVMFuzzerTestOneInput(const char *data, size_t size) {
  xsltFuzzStylesheet(data, size);
  return 0;
}