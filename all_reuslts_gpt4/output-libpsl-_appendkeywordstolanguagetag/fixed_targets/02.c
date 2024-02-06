#include <stdint.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int _appendKeywordsToLanguageTag(char * localeID, char * appendAt, int capacity, char strict, char hadPosix, int * status);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  const std::string localeID = stream.ConsumeRandomLengthString();
  const std::string appendAt = stream.ConsumeRandomLengthString();

  int capacity = stream.ConsumeIntegral<int>();
  char strict = stream.ConsumeBool();
  char hadPosix = stream.ConsumeBool();
  int status = 0;

  _appendKeywordsToLanguageTag(const_cast<char*>(localeID.c_str()), const_cast<char*>(appendAt.c_str()), capacity, strict, hadPosix, &status);

  return 0;
}