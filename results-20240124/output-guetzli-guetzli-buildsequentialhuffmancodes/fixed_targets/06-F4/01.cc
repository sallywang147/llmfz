#include <stddef.h>
#include <stdint.h>
#include <vector>

namespace guetzli {

struct JPEGData {
  const uint8_t* data;
  size_t size;
};

struct HuffmanCode {
  uint16_t code;
  uint8_t length;
};

void BuildSequentialHuffmanCodes(JPEGData* jdata,
                                 std::vector<HuffmanCode>* codes,
                                 std::vector<int>* code_lengths);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  JPEGData jdata = {data, size};

  std::vector<HuffmanCode> codes;
  std::vector<int> code_lengths;

  BuildSequentialHuffmanCodes(&jdata, &codes, &code_lengths);

  return 0;
}

}  // namespace guetzli