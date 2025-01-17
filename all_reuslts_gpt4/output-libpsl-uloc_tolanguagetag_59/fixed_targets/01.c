#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unicode/uloc.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string localeID = stream.ConsumeRandomLengthString();
  int langtagCapacity = stream.ConsumeIntegral<int>();
  char strict = stream.ConsumeBool();
  int status = 0;

  char* langtag = (char*) malloc(sizeof(char) * (langtagCapacity >= 0 ? langtagCapacity : 0));

  if (langtag == NULL) {
    return 0;
  }

  uloc_toLanguageTag_59(const_cast<char*>(localeID.c_str()), langtag, langtagCapacity, strict, &status);

  free(langtag);

  return 0;
}