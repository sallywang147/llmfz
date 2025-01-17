 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "gzip.h"

namespace freetype {

class GzipFuzzTarget {
 public:
  void GzipFuzzTarget(GzipFuzzTarget* this_) {
    FuzzedDataProvider stream(data, size);

    std::vector<uint8_t> compressed_data =
        stream.ConsumeRemainingBytes<uint8_t>();
    std::vector<uint8_t> decompressed_data;
    decompressed_data.resize(compressed_data.size() * 10);
    size_t decompressed_size = decompressed_data.size();
    int ret = uncompress(decompressed_data.data(), &decompressed_size,
                         compressed_data.data(), compressed_data.size());
    if (ret != Z_OK) {
      return;
    }
    decompressed_data.resize(decompressed_size);
  }

 private:
  const uint8_t* data;
  size_t size;
};

}  // namespace freetype

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  freetype::GzipFuzzTarget target;
  target.GzipFuzzTarget(&target);
  return 0;
}