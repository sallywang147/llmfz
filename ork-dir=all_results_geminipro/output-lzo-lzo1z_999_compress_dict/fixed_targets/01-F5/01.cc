#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" {
#include "lzo/lzoconf.h"  // Include the header file that contains the declaration of lzo1z_999_compress_dict
#include "lzo/lzo1z.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t in_len = stream.ConsumeIntegralInRange<size_t>(0, size);
  const size_t out_len = stream.ConsumeIntegralInRange<size_t>(0, size);
  const size_t dict_len = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<uint8_t> in_data = stream.ConsumeBytes<uint8_t>(in_len);
  std::vector<uint8_t> out_data(out_len);
  std::vector<uint8_t> dict_data = stream.ConsumeBytes<uint8_t>(dict_len);
  std::vector<uint8_t> wrkmem(LZO1Z_999_MEM_COMPRESS);

  int ret = lzo1z_999_compress_dict(reinterpret_cast<char*>(in_data.data()),
                                   in_len, reinterpret_cast<char*>(out_data.data()),
                                   &out_len, reinterpret_cast<char*>(wrkmem.data()),
                                   reinterpret_cast<char*>(dict_data.data()),
                                   dict_len);
  if (ret != LZO_E_OK) {
    return 0;
  }
  return 0;
}