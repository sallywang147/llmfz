#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tidy.h"
#include "tidybuffio.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    tidyInit();
    initialized = true;
  }
  TidyDoc tdoc = tidyCreate();
  TidyBuffer fuzz_toutput;
  TidyBuffer fuzz_terror;

  tidyBufInit(&fuzz_toutput);
  tidyBufInit(&fuzz_terror);

  tidySetErrorBuffer(tdoc, &fuzz_terror);
  tidySetOutputBuffer(tdoc, &fuzz_toutput);

  TidyInputSource source;
  source.type = TidyInputSourceFile;
  source.fp = nullptr;
  source.next = nullptr;

  FuzzedDataProvider provider(data, size);
  if (provider.remaining_bytes() == 0) {
    // Nothing to fuzz.
    tidyRelease(tdoc);
    tidyBufFree(&fuzz_toutput);
    tidyBufFree(&fuzz_terror);
    return 0;
  }

  const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
      0,
      provider.remaining_bytes());
  auto next_input = provider.ConsumeBytes<char>(next_size);
  source.data = next_input.data();
  source.size = next_input.size();

  tidyParseSource(tdoc, &source);

  tidyRelease(tdoc);
  tidyBufFree(&fuzz_toutput);
  tidyBufFree(&fuzz_terror);

  return 0;
}