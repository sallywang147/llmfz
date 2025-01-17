#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "7z.h"
#include "XzEnc.h"

struct ISeqOutStream {
  size_t (*Write)(const ISeqOutStream* p, const void* buf, size_t size);
};

struct ISeqInStream {
  size_t (*Read)(const ISeqInStream* p, void* buf, size_t size);
};

struct CXzProps {
  uint32_t lzma2Prop;
  uint32_t dictSize;
  uint32_t lc;
  uint32_t lp;
  uint32_t pb;
  uint32_t numThreads;
};

struct ICompressProgress {
  SRes (*Progress)(const ICompressProgress* p, uint64_t inSize, uint64_t outSize);
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct ISeqOutStream outStream;
  struct ISeqInStream inStream;
  struct CXzProps props;
  struct ICompressProgress progress;

  // Initialize the properties
  props.lzma2Prop = stream.ConsumeIntegral<uint32_t>();
  props.dictSize = stream.ConsumeIntegral<uint32_t>();
  props.lc = stream.ConsumeIntegral<uint32_t>();
  props.lp = stream.ConsumeIntegral<uint32_t>();
  props.pb = stream.ConsumeIntegral<uint32_t>();
  props.numThreads = stream.ConsumeIntegral<uint32_t>();

  // Call the function with the initialized parameters
  int result = Xz_Encode(&outStream, &inStream, &props, &progress);

  return 0;
}