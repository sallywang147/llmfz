 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "htslib/hts.h"
#include "htslib/sam.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string input_path =
      stream.ConsumeRemainingBytesAsString();
  const std::string index_path =
      stream.ConsumeRemainingBytesAsString();
  const int min_shift = stream.ConsumeIntegral<int>();
  sam_index_build2(const_cast<char*>(input_path.c_str()),
                    const_cast<char*>(index_path.c_str()), min_shift);
  return 0;
}