#include <stddef.h>
#include <stdint.h>
#include <vector>

namespace guetzli {

void BuildSequentialHuffmanCodes(JPEGData* jdata,
                                 std::vector<HuffmanCode>* codes,
                                 std::vector<int>* code_lengths);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  JPEGData* jdata = new JPEGData();
  jdata->data = data;
  jdata->size = size;

  std::vector<HuffmanCode> codes;
  std::vector<int> code_lengths;

  BuildSequentialHuffmanCodes(jdata, &codes, &code_lengths);

  delete jdata;

  return 0;
}

}  // namespace guetzli