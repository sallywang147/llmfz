#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <unicode/casemap.h>
#include <unicode/edits.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // We need at least one byte for locale and one for options
  if (size < 2) {
    return 0;
  }

  // Consume 1 byte for locale
  std::string locale = stream.ConsumeBytesAsString(1);

  // Consume 1 byte for options
  int options = stream.ConsumeIntegral<int>();

  // Consume half of the remaining bytes for src
  size_t srcLength = stream.remaining_bytes() / 2;
  std::vector<short> src = stream.ConsumeIntegralInRange<short>(0, srcLength);

  // Consume the rest of the bytes for dest
  size_t destCapacity = stream.remaining_bytes();
  std::vector<short> dest(destCapacity);

  icu_59::Edits edits;
  int errorCode = 0;

  icu_59::CaseMap::toUpper(locale.c_str(), options, src.data(), srcLength, dest.data(), destCapacity, &edits, &errorCode);

  return 0;
}