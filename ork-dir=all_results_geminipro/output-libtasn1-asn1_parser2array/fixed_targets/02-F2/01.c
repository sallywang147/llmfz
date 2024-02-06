#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "asn1_parser2array.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string input_file_name = stream.ConsumeRemainingBytesAsString();
  const std::string output_file_name = stream.ConsumeRemainingBytesAsString();
  const std::string vector_name = stream.ConsumeRemainingBytesAsString();
  const std::string error_desc = stream.ConsumeRemainingBytesAsString();

  int ret = asn1_parser2array(
      input_file_name.c_str(),
      output_file_name.c_str(),
      vector_name.c_str(),
      error_desc.c_str());

  return ret;
}
```

The issue is that the `asn1_parser2array` function expects `const char*` arguments, but the code was passing `char*` arguments. This can cause undefined behavior.

To fix the issue, the code was changed to pass `const char*` arguments to the `asn1_parser2array` function.