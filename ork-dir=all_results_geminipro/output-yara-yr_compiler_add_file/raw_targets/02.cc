#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "yacc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  YR_COMPILER* compiler = yr_compiler_new();
  if (compiler == nullptr) {
    return 0;
  }

  const std::string rules_file_name = stream.ConsumeRemainingBytesAsString();
  FILE* rules_file = fopen(rules_file_name.c_str(), "r");
  if (rules_file == nullptr) {
    yr_compiler_delete(compiler);
    return 0;
  }

  const std::string namespace_ = stream.ConsumeRemainingBytesAsString();
  const std::string file_name = stream.ConsumeRemainingBytesAsString();

  int result = yr_compiler_add_file(compiler, rules_file,
                                    const_cast<char*>(namespace_.c_str()),
                                    const_cast<char*>(file_name.c_str()));
  yr_compiler_delete(compiler);
  fclose(rules_file);
  return result;
}