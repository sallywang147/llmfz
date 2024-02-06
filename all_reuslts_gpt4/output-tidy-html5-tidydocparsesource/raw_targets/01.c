#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "tidy.h"
#include "tidybuffio.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  TidyBuffer buffer = {0};
  tidyBufAttach(&buffer, const_cast<uint8_t*>(data), size);
  TidyInputSource input_source;
  tidyInitSource(&input_source, &buffer, tidyGetByte, tidyUngetByte);

  TidyDoc doc = tidyCreate();
  tidyOptSetBool(doc, TidyForceOutput, yes);  // Ensure the document is output even if errors are detected.
  tidyOptSetBool(doc, TidyMark, no);  // No HTML tidy meta tag inserted in output.
  tidyOptSetInt(doc, TidyWrapLen, 0xFFFFFFFF);  // No line wrapping.
  tidySetCharEncoding(doc, "raw");
  tidyDocParseSource(doc, &input_source);
  tidyBufDetach(&buffer);

  tidyRelease(doc);
  return 0;
}