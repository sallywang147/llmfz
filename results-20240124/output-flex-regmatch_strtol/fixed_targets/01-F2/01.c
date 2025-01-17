#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <regex.h>
#include <regex>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Create a regular expression.
  const std::string regex_string = provider.ConsumeRemainingBytesAsString();
  const char* regex_cstr = regex_string.c_str();

  // Compile the regular expression.
  regex_t regex;
  if (regcomp(&regex, regex_cstr, REG_EXTENDED) != 0) {
    return 0;
  }

  // Create a string to match against.
  const std::string input_string = provider.ConsumeRemainingBytesAsString();
  const char* input_cstr = input_string.c_str();

  // Match the regular expression against the string.
  regmatch_t match;
  if (regexec(&regex, input_cstr, 1, &match, 0) != 0) {
    regfree(&regex);
    return 0;
  }

  // Convert the matched substring to an integer.
  char* endptr;
  int base = provider.ConsumeIntegralInRange<int>(2, 36);
  int value = std::regex_search(input_string, std::regex(regex_string)) ? regmatch_strtol(&match, input_cstr, &endptr, base) : 0;

  // Free the regular expression.
  regfree(&regex);

  return 0;
}