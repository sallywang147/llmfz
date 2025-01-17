#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "unicode/appendable.h"
#include "unicode/fieldpos.h"
#include "unicode/fmtable.h"
#include "unicode/messageformat.h"
#include "unicode/unistr.h"

class AppendableWrapper : public icu_75::Appendable {
 public:
  icu_75::UnicodeString& appendCodeUnit(icu_75::UChar c) override {
    return str_.append(c);
  }
  icu_75::UnicodeString& append(const icu_75::UnicodeString& s) override {
    return str_.append(s);
  }
  icu_75::UnicodeString& append(const icu_75::UnicodeString& s, int32_t start,
                                int32_t length) override {
    return str_.append(s, start, length);
  }

 private:
  icu_75::UnicodeString str_;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  icu_75::MessageFormat message_format(provider.ConsumeRandomLengthString().c_str(), icu_75::Locale::getDefault());
  int msgStart = provider.ConsumeIntegral<int>();
  char plNumber = provider.ConsumeIntegral<char>();
  int cnt = provider.ConsumeIntegral<int>();
  std::vector<icu_75::Formattable> arguments(cnt);
  std::vector<icu_75::UnicodeString> argumentNames(cnt);
  AppendableWrapper appendTo;
  icu_75::FieldPosition ignore;
  int success;

  message_format.format(&message_format, msgStart, &plNumber, arguments.data(), argumentNames.data(), cnt, &appendTo, &ignore, &success);

  return 0;
}