#include <fuzzer/FuzzedDataProvider.h>
#include <znc/ZNCString.h>
#include <znc/ZNC.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    // Not enough data to split into two strings
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string str1 = stream.ConsumeBytesAsString(size / 2);
  std::string str2 = stream.ConsumeRemainingBytesAsString();

  CString s1(str1.c_str());
  CString s2(str2.c_str());

  CZNC znc;

  znc.ParseConfig(&znc, &s1, &s2);

  return 0;
}