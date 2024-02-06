#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "rawspeed_api.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  rawspeed::CameraMetaData camDB;
  rawspeed::RawParser t(data, size);
  rawspeed::RawDecoder *d = t.getDecoder();
  if (!d) {
    return 0;
  }

  d->failOnUnknown = false;
  d->checkSupport(&camDB);
  d->decodeRaw();
  d->decodeMetaData(&camDB);

  rawspeed::RawImage r = d->mRaw;

  rawspeed::ArwDecoder *arw_decoder = dynamic_cast<rawspeed::ArwDecoder*>(d);
  if (arw_decoder) {
    arw_decoder->decodeSRF(&r, arw_decoder);
  }

  delete d;

  return 0;
}