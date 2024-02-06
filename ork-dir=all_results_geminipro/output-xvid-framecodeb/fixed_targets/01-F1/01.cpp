#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>

struct Encoder {
  int a;
  int b;
};

struct FRAMEINFO {
  int c;
  int d;
};

struct Bitstream {
  int e;
  int f;
};

extern "C" {
#include "FrameCodeB.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Encoder encoder;
  encoder.a = stream.ConsumeIntegral<int>();
  encoder.b = stream.ConsumeIntegral<int>();

  FRAMEINFO frame;
  frame.c = stream.ConsumeIntegral<int>();
  frame.d = stream.ConsumeIntegral<int>();

  Bitstream bs;
  bs.e = stream.ConsumeIntegral<int>();
  bs.f = stream.ConsumeIntegral<int>();

  FrameCodeB(&encoder, &frame, &bs);

  return 0;
}