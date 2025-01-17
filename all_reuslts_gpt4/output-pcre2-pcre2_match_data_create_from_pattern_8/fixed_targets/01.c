#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pcre2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Prepare general context
  struct pcre2_real_general_context_8* gcontext = pcre2_real_general_context_create_8(NULL, NULL, NULL);
  if (gcontext == NULL) {
    return 0;
  }

  // Prepare pattern
  std::string pattern = stream.ConsumeRandomLengthString();
  int errorcode;
  PCRE2_SIZE erroroffset;
  struct pcre2_real_code_8* code = pcre2_real_compile_8((PCRE2_SPTR8)pattern.c_str(), pattern.size(), 0, &errorcode, &erroroffset, NULL);
  if (code == NULL) {
    pcre2_real_general_context_free_8(gcontext);
    return 0;
  }

  // Call the target function
  struct pcre2_real_match_data_8* match_data = pcre2_match_data_create_from_pattern_8(code, gcontext);

  // Cleanup
  pcre2_match_data_free_8(match_data);
  pcre2_real_code_free_8(code);
  pcre2_real_general_context_free_8(gcontext);

  return 0;
}