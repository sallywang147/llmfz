#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data for struct _Str
  struct _Str input_str;
  input_str.length = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<char> str_data = stream.ConsumeBytes<char>(input_str.length);
  input_str.p = str_data.data();

  // Consume data for ces
  int ces = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  struct _Str *output_str = wc_conv_from_utf7(&input_str, ces);

  // Free memory if output_str is not null
  if (output_str != nullptr) {
    free(output_str);
  }

  return 0;
}