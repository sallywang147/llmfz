#include <cstring>

#include "fuzzer_utils.h"

extern "C" {
#include "unicode/messageformat.h"
#include "unicode/formattable.h"
#include "unicode/appendable.h"
#include "unicode/fieldpos.h"
#include "unicode/locid.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Set the limit for the test data to 1000 bytes to avoid timeout for a
  // very long list of operations.
  if (size > 1000) {
    size = 1000;
  }
  icu::StringPiece fuzzData(reinterpret_cast<const char *>(data), size);
  // Byte 0 randomly select a Locale
  uint16_t rnd;
  std::memcpy(&rnd, fuzzData.data(), sizeof(rnd));
  fuzzData.remove_prefix(sizeof(rnd));
  icu::Locale locale = GetRandomLocale(rnd);

  // Byte 1 randomly select a Formattable type
  uint8_t type = *fuzzData.data();
  fuzzData.remove_prefix(1);
  icu::Formattable formattable;
  switch (type % 4) {
  case 0:
    formattable.setDouble(GetRandomDouble(fuzzData));
    break;
  case 1:
    formattable.setInt64(GetRandomInt64(fuzzData));
    break;
  case 2:
    formattable.setString(GetRandomString(fuzzData));
    break;
  case 3:
    formattable.setObject(GetRandomObject(fuzzData));
    break;
  }

  // Byte 2 randomly select a MessageFormat pattern
  icu::UnicodeString pattern = GetRandomPattern(fuzzData);

  // Byte 3 randomly select a FieldPosition
  icu::FieldPosition fieldPosition;
  uint8_t fieldType = *fuzzData.data();
  fuzzData.remove_prefix(1);
  switch (fieldType % 3) {
  case 0:
    fieldPosition.setField(icu::Formattable::kIntegerField);
    break;
  case 1:
    fieldPosition.setField(icu::Formattable::kDoubleField);
    break;
  case 2:
    fieldPosition.setField(icu::Formattable::kStringField);
    break;
  }

  // Byte 4 randomly select a AppendableWrapper
  icu::UnicodeString str;
  icu::AppendableWrapper appendableWrapper(str);

  // Byte 5 randomly select a success
  int success = *fuzzData.data();
  fuzzData.remove_prefix(1);

  // Byte 6 randomly select a msgStart
  int msgStart = *fuzzData.data();
  fuzzData.remove_prefix(1);

  // Byte 7 randomly select a plNumber
  char plNumber = *fuzzData.data();
  fuzzData.remove_prefix(1);

  // Byte 8 randomly select a cnt
  int cnt = *fuzzData.data();
  fuzzData.remove_prefix(1);

  // Byte 9 randomly select a argumentNames
  icu::UnicodeString argumentNames;
  if (cnt > 0) {
    argumentNames = GetRandomString(fuzzData);
  }

  // Byte 10 randomly select a arguments
  icu::Formattable arguments[cnt];
  for (int i = 0; i < cnt; i++) {
    switch (type % 4) {
    case 0:
      arguments[i].setDouble(GetRandomDouble(fuzzData));
      break;
    case 1:
      arguments[i].setInt64(GetRandomInt64(fuzzData));
      break;
    case 2:
      arguments[i].setString(GetRandomString(fuzzData));
      break;
    case 3:
      arguments[i].setObject(GetRandomObject(fuzzData));
      break;
    }
  }

  icu::MessageFormat formatter(pattern, locale);
  formatter.format(msgStart, &plNumber, arguments, &argumentNames, cnt, &appendableWrapper, &fieldPosition, &success);

  return EXIT_SUCCESS;
}