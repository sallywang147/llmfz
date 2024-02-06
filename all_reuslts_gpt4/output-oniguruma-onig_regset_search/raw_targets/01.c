#include <fuzzer/FuzzedDataProvider.h>
#include <oniguruma.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string pattern = stream.ConsumeRandomLengthString();
  std::string str = stream.ConsumeRemainingBytesAsString();
  char* start = const_cast<char*>(str.c_str());
  char* end = start + str.size();
  char* range = end;

  OnigErrorInfo einfo;
  OnigRegex regex = onig_new((OnigUChar*)pattern.c_str(), (OnigUChar*)(pattern.c_str() + pattern.size()), ONIG_OPTION_DEFAULT, ONIG_ENCODING_UTF8, ONIG_SYNTAX_DEFAULT, &einfo);
  if (!regex) {
    return 0;
  }

  OnigRegSetStruct* set = onig_regset_new(&regex, 1);
  if (!set) {
    onig_free(regex);
    return 0;
  }

  int rmatch_pos;
  int lead = stream.ConsumeIntegral<int>();
  int option = stream.ConsumeIntegral<int>();

  onig_regset_search(set, (OnigUChar*)start, (OnigUChar*)end, (OnigUChar*)start, (OnigUChar*)range, lead, option, &rmatch_pos);

  onig_regset_free(set);
  onig_free(regex);

  return 0;
}