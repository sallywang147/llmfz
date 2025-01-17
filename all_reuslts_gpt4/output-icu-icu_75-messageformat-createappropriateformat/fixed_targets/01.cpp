#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "unicode/messageformat.h"
#include "unicode/parseerr.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  UErrorCode status = U_ZERO_ERROR;
  UParseError parseError;
  int formattableType = stream.ConsumeIntegral<int>();

  std::string type = stream.ConsumeRandomLengthString();
  icu_75::UnicodeString uType(type.c_str(), type.size());

  std::string style = stream.ConsumeRandomLengthString();
  icu_75::UnicodeString uStyle(style.c_str(), style.size());

  icu_75::MessageFormat msgFormat(uType, status);
  if (U_FAILURE(status)) {
    return 0;
  }

  icu_75::Format* format = msgFormat.createAppropriateFormat(&msgFormat, &uType, &uStyle, &formattableType, &parseError, &status);
  delete format;

  return 0;
}