#include <cstring>

#include "fuzzer_utils.h"

#include "unicode/messageformat.h"
#include "unicode/unistr.h"

#include "unicode/uversion.h"

extern "C" {
#include "unicode/ustring.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Check the ICU version to ensure compatibility.
  if (U_ICU_VERSION < 63) {
    return EXIT_FAILURE;
  }

  icu::StringPiece fuzzData(reinterpret_cast<const char *>(data), size);
  int32_t status = 0;
  icu::MessageFormat fmt(icu::UnicodeString(), status);
  if (U_FAILURE(status)) {
    return EXIT_FAILURE;
  }

  while (fuzzData.length() > 0) {
    uint8_t command = *fuzzData.data();
    fuzzData.remove_prefix(1);

    switch (command % 4) {
    case 0:
      printf("setLocale(%s)\n", GetRandomLocaleString(fuzzData).c_str());
      fmt.setLocale(icu::Locale(GetRandomLocaleString(fuzzData).c_str()));
      break;
    case 1:
      printf("applyPattern(%s)\n", GetRandomPatternString(fuzzData).c_str());
      fmt.applyPattern(icu::UnicodeString(GetRandomPatternString(fuzzData).c_str()), status);
      break;
    case 2:
      printf("format(string)\n");
      {
        icu::UnicodeString arg = GetRandomString(fuzzData);
        icu::UnicodeString result;
        fmt.format(arg, result, status);
      }
      break;
    case 3:
      printf("format(list)\n");
      {
        icu::UnicodeString arg = GetRandomString(fuzzData);
        icu::UnicodeString result;
        fmt.format(arg, result, status);
      }
      break;
    default:
      break;
    }
  }

  fmt.cacheExplicitFormats(status);

  return EXIT_SUCCESS;
}