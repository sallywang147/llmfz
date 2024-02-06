#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <pcre2.h>
#include <pcre2posix.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct pcre2_real_general_context_8* gcontext =
      pcre2_general_context_create_8(PCRE2_CONFIG_DEFAULT, nullptr);
  if (gcontext == nullptr) {
    return 0;
  }
  struct pcre2_real_compile_context_8* ccontext =
      pcre2_compile_context_create_8(gcontext);
  if (ccontext == nullptr) {
    pcre2_general_context_free_8(gcontext);
    return 0;
  }
  const char* pattern = stream.ConsumeRemainingBytesAsString().c_str();
  int errorcode;
  PCRE2_SIZE erroroffset;
  PCRE2_SPTR pattern_ptr = reinterpret_cast<PCRE2_SPTR>(pattern);
  PCRE2_SIZE pattern_length = strlen(pattern);
  int compile_rc = pcre2_compile_8(ccontext, pattern_ptr, pattern_length, 0,
                                  &errorcode, &erroroffset, nullptr);
  if (compile_rc != 0) {
    pcre2_compile_context_free_8(ccontext);
    pcre2_general_context_free_8(gcontext);
    return 0;
  }
  pcre2_compile_context_free_8(ccontext);
  pcre2_general_context_free_8(gcontext);
  return 0;
}