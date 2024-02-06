#include <cstring>
#include <iostream>
#include <exception>
#include <string>

#include "fuzzer_utils.h"

#include "unicode/messageformat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2)
    return 0;

  icu::StringPiece fuzzData(reinterpret_cast<const char *>(data), size);

  int status = 0;
  icu::MessageFormat fmt;
  fmt.cacheExplicitFormats(&status);
  if (U_FAILURE(status))
    return 0;

  std::string formatted;
  try {
    formatted = fmt.format(fuzzData, &status);
  } catch (const std::exception &e) {
    std::cerr << "Caught exception: " << e.what() << std::endl;
    return 0;
  }
  if (U_FAILURE(status))
    return 0;

  return EXIT_SUCCESS;
}