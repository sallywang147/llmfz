#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" {
#include "7z.h"
#include "7zAlloc.h"
#include "7zBuf.h"
#include "7zCrc.h"
#include "7zFile.h"
#include "7zVersion.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize Xz encoder.
  CXzStream xz_stream;
  Xz_Init(&xz_stream);

  // Set Xz encoder properties.
  CXzProps props;
  Xz_SetDefaultProps(&props);
  props.dictSize = stream.ConsumeIntegralInRange<UInt64>(1 << 12, 1 << 24);
  props.numThreads = stream.ConsumeIntegralInRange<UInt32>(1, 16);
  props.lzmaProps.lc = stream.ConsumeIntegralInRange<UInt32>(0, 8);
  props.lzmaProps.lp = stream.ConsumeIntegralInRange<UInt32>(0, 4);
  props.lzmaProps.pb = stream.ConsumeIntegralInRange<UInt32>(0, 4);

  // Initialize Xz input stream.
  CSeqInStream in_stream;
  SeqInStream_CreateVTable(&in_stream);
  in_stream.Read = [](void* pp, void* buf, size_t size) {
    FuzzedDataProvider* stream = (FuzzedDataProvider*)pp;
    size_t bytes_to_consume = std::min(size, stream->remaining_bytes());
    auto bytes = stream->ConsumeBytes<uint8_t>(bytes_to_consume);
    std::memcpy(buf, bytes.data(), bytes.size());
    return bytes.size();
  };
  in_stream.Skip = [](void* pp, UInt64 offset) {
    FuzzedDataProvider* stream = (FuzzedDataProvider*)pp;
    stream->ConsumeBytes<uint8_t>(static_cast<size_t>(offset));
    return 0;
  };
  in_stream.pp = &stream;

  // Initialize Xz output stream.
  CSeqOutStream out_stream;
  SeqOutStream_CreateVTable(&out_stream);
  out_stream.Write = [](void* pp, const void* buf, size_t size) { return 0; };
  out_stream.Flush = [](void* pp) { return 0; };
  out_stream.pp = nullptr;

  // Initialize Xz progress object.
  ICompressProgress progress;
  CompressProgress_Init(&progress);

  // Encode data.
  int ret = Xz_Encode(&out_stream, &in_stream, &props, &progress);
  if (ret != SZ_OK) {
    return 0;
  }

  // Clean up.
  Xz_Free(&xz_stream);
  SeqInStream_Destroy(&in_stream);
  SeqOutStream_Destroy(&out_stream);
  CompressProgress_Free(&progress);

  return 0;
}