#include <cstring>

#include "fuzzer_utils.h"

#include "unicode/messageformat.h"
#include "unicode/formattable.h"
#include "unicode/appendable.h"
#include "unicode/fieldpos.h"

extern "C" {
#include "unicode/utypes.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  uint16_t rnd;
  // Set the limit for the test data to 1000 bytes to avoid timeout for a
  // very long list of operations.
  if (size > 1000) {
    size = 1000;
  }
  if (size < 3 * sizeof(rnd) + 1)
    return 0;
  icu::StringPiece fuzzData(reinterpret_cast<const char *>(data), size);
  // Byte 0 and 1 randomly select a MessageFormat
  std::memcpy(&rnd, fuzzData.data(), sizeof(rnd));
  fuzzData.remove_prefix(sizeof(rnd));
  std::unique_ptr<icu::MessageFormat> fmt(CreateRandomMessageFormat(rnd));

  // Byte 1 and 2 randomly select a Formattable
  std::memcpy(&rnd, fuzzData.data(), sizeof(rnd));
  fuzzData.remove_prefix(sizeof(rnd));
  icu::Formattable fmtArg = GetRandomFormattable(rnd);

  // Byte 2 randomly select a FieldPosition
  std::memcpy(&rnd, fuzzData.data(), sizeof(rnd));
  fuzzData.remove_prefix(sizeof(rnd));
  icu::FieldPosition pos(rnd);

  // Byte 3 randomly select a AppendableWrapper
  std::memcpy(&rnd, fuzzData.data(), sizeof(rnd));
  fuzzData.remove_prefix(sizeof(rnd));
  icu::AppendableWrapper wrapper(GetRandomAppendable(rnd));

  int msgStart = *fuzzData.data();
  fuzzData.remove_prefix(1);

  int success = 0;
  fmt->format(msgStart, nullptr, &fmtArg, nullptr, 0, &wrapper, &pos, &success);

  return EXIT_SUCCESS;
}