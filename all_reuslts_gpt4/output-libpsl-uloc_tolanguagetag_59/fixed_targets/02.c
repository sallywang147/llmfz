#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "fuzzer/FuzzedDataProvider.h"

extern "C" int uloc_toLanguageTag_59(char * localeID, char * langtag, int langtagCapacity, char strict, int * status);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data for localeID
  std::string localeID = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  
  // Consume data for langtag
  std::string langtag = stream.ConsumeRemainingBytesAsString();

  // Initialize langtagCapacity
  int langtagCapacity = langtag.size();

  // Initialize strict
  char strict = stream.ConsumeBool();

  // Initialize status
  int status = 0;

  // Call the function
  uloc_toLanguageTag_59(const_cast<char*>(localeID.c_str()), const_cast<char*>(langtag.c_str()), langtagCapacity, strict, &status);

  return 0;
}