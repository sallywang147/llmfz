#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "rawspeed/RawSpeed-API.h"
#include "rawspeed/NakedDecoder.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  rawspeed::Buffer buffer(data, size);
  rawspeed::RawParser parser(&buffer);
  std::unique_ptr<rawspeed::RawDecoder> decoder(parser.getDecoder());

  if (decoder.get() == nullptr) {
    return 0;
  }
  
  rawspeed::NakedDecoder* nakedDecoder = dynamic_cast<rawspeed::NakedDecoder*>(decoder.get());
  if (nakedDecoder == nullptr) {
    return 0;
  }

  decoder->failOnUnknown = false;
  decoder->checkSupport();
  decoder->decodeMetaData();

  rawspeed::RawImage raw = decoder->mRaw;

  nakedDecoder->decodeRawInternal(&raw, nakedDecoder);

  return 0;
}