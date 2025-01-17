#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "7z.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a stream to read the input data from.
  ISeqInStream inStream;
  inStream.Read = [](void* p, void* buf, size_t size) {
    auto* stream = static_cast<FuzzedDataProvider*>(p);
    auto bytes = stream->ConsumeBytes<uint8_t>(size);
    memcpy(buf, bytes.data(), bytes.size());
    return bytes.size();
  };
  inStream.Skip = [](void* p, Int64 amount) {
    auto* stream = static_cast<FuzzedDataProvider*>(p);
    stream->ConsumeBytes<uint8_t>(amount);
    return 0;
  };
  inStream.p = &stream;

  // Create a stream to write the compressed data to.
  std::vector<uint8_t> compressed;
  ISeqOutStream outStream;
  outStream.Write = [](void* p, const void* buf, size_t size) {
    auto* compressed = static_cast<std::vector<uint8_t>*>(p);
    compressed->insert(compressed->end(),
                       static_cast<const uint8_t*>(buf),
                       static_cast<const uint8_t*>(buf) + size);
    return size;
  };
  outStream.Flush = [](void* p) { return 0; };
  outStream.p = &compressed;

  // Create a progress object.
  ICompressProgress progress;
  progress.InSize = stream.remaining_bytes();
  progress.OutSize = 0;

  // Create a properties object.
  CXzProps props;
  props.lzma2.dictSize = stream.ConsumeIntegralInRange<UInt32>(1 << 12, 1 << 24);
  props.lzma2.numFastBytes = stream.ConsumeIntegralInRange<UInt32>(5, 255);
  props.lzma2.numMatchFinderCycles =
      stream.ConsumeIntegralInRange<UInt32>(1, LZMA_NUM_MATCH_FINDER_CYCLES);
  props.lzma2.numBlockThreads = stream.ConsumeIntegralInRange<UInt32>(1, 64);

  // Compress the data.
  int ret = Xz_Encode(&outStream, &inStream, &props, &progress);
  if (ret != SZ_OK) {
    return 0;
  }

  return 0;
}