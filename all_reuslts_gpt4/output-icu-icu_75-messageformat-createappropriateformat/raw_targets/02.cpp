#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "unicode/messageformat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  UErrorCode status = U_ZERO_ERROR;
  UParseError parseError;
  int32_t formattableType = 0;

  icu_75::UnicodeString type = icu_75::UnicodeString::fromUTF8(provider.ConsumeRandomLengthString().c_str());
  icu_75::UnicodeString style = icu_75::UnicodeString::fromUTF8(provider.ConsumeRandomLengthString().c_str());

  icu_75::MessageFormat msgFormat("", status);
  if (U_FAILURE(status)) {
    return 0;
  }

  icu_75::Format* format = msgFormat.createAppropriateFormat(&msgFormat, &type, &style, &formattableType, &parseError, &status);
  if (U_SUCCESS(status)) {
    delete format;
  }

  return 0;
}