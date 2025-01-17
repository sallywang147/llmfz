#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include <regex.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const uint8_t regex_size = stream.ConsumeIntegral<uint8_t>();
  const std::string regex = stream.ConsumeBytesAsString(regex_size);

  const uint8_t input_size = stream.ConsumeIntegral<uint8_t>();
  const std::string input = stream.ConsumeBytesAsString(input_size);

  const uint8_t base = stream.ConsumeIntegral<uint8_t>();

  regex_t re;
  if (regcomp(&re, regex.c_str(), REG_EXTENDED) != 0) {
    return 0;
  }

  regmatch_t matches[re.re_nsub + 1];
  if (regexec(&re, input.c_str(), re.re_nsub + 1, matches, 0) != 0) {
    regfree(&re);
    return 0;
  }

  for (size_t i = 0; i <= re.re_nsub; i++) {
    if (matches[i].rm_so == -1) {
      continue;
    }
    const std::string match =
        input.substr(matches[i].rm_so, matches[i].rm_eo - matches[i].rm_so);
    char* endptr;
    // Fix the error: use of undeclared identifier 'regmatch_strtol'
    long regmatch_strtol(const regmatch_t* match, const char* string, char** endptr, int base);
    regmatch_strtol(&matches[i], const_cast<char*>(match.c_str()), &endptr, base);
    if (endptr != match.c_str() + match.size()) {
      fprintf(stderr, "regmatch_strtol failed\n");
    }
  }

  regfree(&re);
  return 0;
}