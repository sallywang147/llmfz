#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int _appendKeywordsToLanguageTag(char * localeID, char * appendAt, int capacity, char strict, char hadPosix, int * status);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // We reserve 1 byte for each of the two strings and 1 byte for each of the two chars.
  const uint8_t max_size = (size - 4) / 2;

  std::string localeID = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<uint8_t>(1, max_size));
  std::string appendAt = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<uint8_t>(1, max_size));
  int capacity = appendAt.size();
  char strict = stream.ConsumeIntegral<char>();
  char hadPosix = stream.ConsumeIntegral<char>();
  int status = 0;

  _appendKeywordsToLanguageTag(const_cast<char*>(localeID.c_str()), const_cast<char*>(appendAt.c_str()), capacity, strict, hadPosix, &status);

  return 0;
}