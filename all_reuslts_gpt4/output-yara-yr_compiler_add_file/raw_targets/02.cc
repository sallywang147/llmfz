#include <fuzzer/FuzzedDataProvider.h>
#include <yara.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  YR_COMPILER* compiler = nullptr;

  if (yr_compiler_create(&compiler) != ERROR_SUCCESS) {
    return 0;
  }

  std::string namespace_ = stream.ConsumeRandomLengthString();
  std::string file_name = stream.ConsumeRandomLengthString();

  std::string rules = stream.ConsumeRemainingBytesAsString();
  FILE* rules_file = fmemopen((void*)rules.data(), rules.size(), "rb");
  if (rules_file == nullptr) {
    yr_compiler_destroy(compiler);
    return 0;
  }

  yr_compiler_add_file(compiler, rules_file, namespace_.c_str(), file_name.c_str());

  fclose(rules_file);
  yr_compiler_destroy(compiler);

  return 0;
}