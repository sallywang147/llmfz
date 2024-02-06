#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "yacc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string namespace_ = stream.ConsumeRemainingBytesAsString();

  const std::string filename = stream.ConsumeRemainingBytesAsString();

  struct _YR_COMPILER* compiler = yr_compiler_new();
  struct _IO_FILE* rules_file = fmemopen(nullptr, 0, "w");
  int ret = yr_compiler_add_file(compiler, rules_file,
                                 const_cast<char*>(namespace_.c_str()),
                                 const_cast<char*>(filename.c_str()));
  yr_compiler_delete(compiler);
  fclose(rules_file);

  return ret;
}