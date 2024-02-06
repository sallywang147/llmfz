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

  // Decompress the data.
  ISeqInStream inStream2;
  inStream2.Read = [](void* p, void* buf, size_t size) {
    auto* compressed = static_cast<std::vector<uint8_t>*>(p);
    if (compressed->size() < size) {
      return 0;
    }
    memcpy(buf, compressed->data(), size);
    compressed->erase(compressed->begin(), compressed->begin() + size);
    return size;
  };
  inStream2.Skip = [](void* p, Int64 amount) {
    auto* compressed = static_cast<std::vector<uint8_t>*>(p);
    if (compressed->size() < amount) {
      return 0;
    }
    compressed->erase(compressed->begin(), compressed->begin() + amount);
    return amount;
  };
  inStream2.p = &compressed;

  ISeqOutStream outStream2;
  outStream2.Write = [](void* p, const void* buf, size_t size) {
    auto* decompressed = static_cast<std::vector<uint8_t>*>(p);
    decompressed->insert(decompressed->end(),
                         static_cast<const uint8_t*>(buf),
                         static_cast<const uint8_t*>(buf) + size);
    return size;
  };
  outStream2.Flush = [](void* p) { return 0; };
  outStream2.p = &decompressed;

  int ret2 = Xz_Decode(&outStream2, &inStream2, &props);
  if (ret2 != SZ_OK) {
    return 0;
  }

  // Compare the original and decompressed data.
  if (decompressed != stream.ConsumeRemainingBytes<std::vector<uint8_t>>()) {
    return 0;
  }

  return 0;
}