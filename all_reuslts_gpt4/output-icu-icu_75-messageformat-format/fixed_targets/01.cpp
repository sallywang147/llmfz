#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "unicode/msgfmt.h"
#include "unicode/utypes.h"
#include "unicode/unistr.h"
#include "unicode/appendable.h"

class AppendableWrapper : public icu_75::Appendable {
 public:
  icu_75::UnicodeString str;

  AppendableWrapper() {}

  virtual ~AppendableWrapper() {}

  icu_75::Appendable &append(icu_75::UChar c) override {
    str += c;
    return *this;
  }

  icu_75::Appendable &append(const icu_75::UChar *s, int32_t length) override {
    str += icu_75::UnicodeString(s, length);
    return *this;
  }
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int msgStart = stream.ConsumeIntegral<int>();
  std::string plNumber = stream.ConsumeRandomLengthString();
  int cnt = stream.ConsumeIntegral<int>();
  icu_75::Formattable arguments[cnt];
  icu_75::UnicodeString argumentNames[cnt];
  AppendableWrapper appendTo;
  icu_75::FieldPosition ignore;
  int success = 0;
  icu_75::MessageFormat msgFormat;
  msgFormat.format(&msgFormat, msgStart, const_cast<char*>(plNumber.c_str()), arguments, argumentNames, cnt, &appendTo, &ignore, &success);
  return 0;
}