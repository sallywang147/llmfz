#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "7z.h"
#include "XzEnc.h"

// Define the required ISeqOutStream and ISeqInStream functions
static SRes SeqInStream_Read(void *p, void *buf, size_t *size) {
  FuzzedDataProvider *provider = static_cast<FuzzedDataProvider*>(p);
  std::vector<uint8_t> data = provider->ConsumeBytes<uint8_t>(*size);
  memcpy(buf, data.data(), data.size());
  *size = data.size();
  return SZ_OK;
}

static size_t SeqOutStream_Write(void *p, const void *buf, size_t size) {
  // We don't need to do anything with the output data, just return the size
  return size;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Initialize the ISeqInStream and ISeqOutStream structs
  ISeqInStream inStream;
  inStream.Read = SeqInStream_Read;
  ISeqOutStream outStream;
  outStream.Write = SeqOutStream_Write;

  // Initialize the CXzProps struct
  CXzProps props;
  XzProps_Init(&props);
  props.lzmaProps.level = provider.ConsumeIntegralInRange<int>(0, 9);
  props.lzmaProps.dictSize = provider.ConsumeIntegral<uint32_t>();
  props.lzmaProps.lc = provider.ConsumeIntegralInRange<int>(0, 8);
  props.lzmaProps.lp = provider.ConsumeIntegralInRange<int>(0, 4);
  props.lzmaProps.pb = provider.ConsumeIntegralInRange<int>(0, 4);
  props.lzmaProps.fb = provider.ConsumeIntegralInRange<int>(5, 273);
  props.lzmaProps.numThreads = provider.ConsumeIntegral<uint32_t>();

  // We don't need to monitor the progress of the encoding, so we'll pass NULL for the ICompressProgress parameter
  int result = Xz_Encode(&outStream, &inStream, &props, NULL);

  return 0;
}