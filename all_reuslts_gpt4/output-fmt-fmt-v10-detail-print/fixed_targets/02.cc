#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <vector>

#include "fmt/core.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  std::string text = stream.ConsumeRandomLengthString();
  FILE *f = tmpfile();
  
  if (f == nullptr) {
    return 0;
  }
  
  fmt::v10::detail::print(f, const_cast<char*>(text.c_str()), text.size());

  fclose(f);

  return 0;
}