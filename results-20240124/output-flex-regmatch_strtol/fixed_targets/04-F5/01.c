#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <regex.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char src[1024];
  // Fix: Use `ConsumeRemainingBytes()` correctly
  size_t src_len = stream.ConsumeRemainingBytes(src, sizeof(src) - 1);
  src[src_len] = '\0'; // Null-terminate the string

  regmatch_t match;
  match.rm_so = stream.ConsumeIntegral<int>();
  match.rm_eo = stream.ConsumeIntegral<int>();

  char* endptr;
  int base = stream.ConsumeIntegral<int>();

  // Fix: Call the target function `regcomp`
  int result = regcomp(&match, src, REG_EXTENDED);
  if (result != 0) {
    // Handle the error
    return 0;
  }

  // Fix: Call the target function `regexec`
  result = regexec(&match, src, 0, NULL, 0);
  if (result != 0) {
    // Handle the error
    return 0;
  }

  // Fix: Call the target function `regfree`
  regfree(&match);

  // Fix: Call the target function `regmatch_strtol`
  regmatch_strtol(&match, src, &endptr, base);

  return 0;
}