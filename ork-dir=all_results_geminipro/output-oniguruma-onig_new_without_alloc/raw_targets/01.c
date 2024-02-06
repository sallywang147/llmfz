#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "oniguruma.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const std::string pattern = provider.ConsumeRemainingBytesAsString();
  struct re_pattern_buffer reg;
  struct OnigEncodingTypeST enc = ONIG_ENCODING_UTF8;
  struct OnigSyntaxType syntax = ONIG_SYNTAX_DEFAULT;
  struct OnigErrorInfo einfo;
  int option = ONIG_OPTION_DEFAULT;
  int ret = onig_new_without_alloc(&reg, const_cast<char*>(pattern.c_str()),
                                 const_cast<char*>(pattern.c_str()) + pattern.size(),
                                 option, &enc, &syntax, &einfo);
  if (ret != ONIG_NORMAL) {
    fprintf(stderr, "Error: %s\n", einfo.par);
  }
  onig_free(&reg);
  return 0;
}