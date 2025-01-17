#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct Encoder {
    int a;
    int b;
    int c;
  };

  struct FRAMEINFO {
    int d;
    int e;
    int f;
  };

  struct Bitstream {
    int g;
    int h;
    int i;
  };

  FuzzedDataProvider provider(data, size);
  Encoder enc;
  enc.a = provider.ConsumeIntegral<int>();
  enc.b = provider.ConsumeIntegral<int>();
  enc.c = provider.ConsumeIntegral<int>();

  FRAMEINFO frame;
  frame.d = provider.ConsumeIntegral<int>();
  frame.e = provider.ConsumeIntegral<int>();
  frame.f = provider.ConsumeIntegral<int>();

  Bitstream bs;
  bs.g = provider.ConsumeIntegral<int>();
  bs.h = provider.ConsumeIntegral<int>();
  bs.i = provider.ConsumeIntegral<int>();

  FrameCodeB(&enc, &frame, &bs);

  return 0;
}