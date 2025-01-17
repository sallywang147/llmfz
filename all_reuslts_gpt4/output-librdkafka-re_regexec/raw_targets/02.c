#include <fuzzer/FuzzedDataProvider.h>
#include "regexp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  
  std::string pattern = stream.ConsumeRandomLengthString();
  int cflags = stream.ConsumeIntegral<int>();
  char *error;
  
  struct Reprog *prog = re_regcomp(pattern.c_str(), cflags, &error);
  if (prog == NULL) {
    return 0;
  }

  std::string input = stream.ConsumeRemainingBytesAsString();
  struct Resub sub;
  int eflags = stream.ConsumeIntegral<int>();

  re_regexec(prog, input.c_str(), &sub, eflags);

  re_regfree(prog);

  return 0;
}