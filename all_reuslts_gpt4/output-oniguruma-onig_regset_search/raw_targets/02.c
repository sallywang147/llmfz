#include <fuzzer/FuzzedDataProvider.h>
#include <oniguruma.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string str = stream.ConsumeRandomLengthString();
  char* start = const_cast<char*>(str.c_str());
  char* end = start + str.size();
  char* range = end;

  int lead = stream.ConsumeIntegral<int>();
  int option = stream.ConsumeIntegral<int>();
  int rmatch_pos = 0;

  OnigRegSetStruct* regset = nullptr;
  int ret = onig_regset_search(regset, start, end, start, range, lead, option, &rmatch_pos);

  return 0;
}