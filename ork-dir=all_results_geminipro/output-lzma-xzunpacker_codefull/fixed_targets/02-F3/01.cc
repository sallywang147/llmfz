#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "7z.h"
#include "7zAlloc.h"
#include "7zCrc.h"
#include "7zFile.h"
#include "7zVersion.h"

extern "C" {
#include "7zExtract.h"
#include "7zIn.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t dest_size = stream.ConsumeIntegralInRange<size_t>(0, 1 << 20);
  std::vector<char> dest(dest_size);

  const size_t src_size = stream.ConsumeIntegralInRange<size_t>(0, 1 << 20);
  std::vector<char> src(src_size);
  stream.ConsumeBytes<char>(src.data(), src_size);

  CXzUnpacker p;
  XzUnpacker_Init(&p);

  size_t dest_len = dest_size;
  size_t src_len = src_size;
  int finish_mode = stream.ConsumeIntegral<int>();
  int status;

  int ret = XzUnpacker_CodeFull(&p, dest.data(), &dest_len, src.data(), &src_len,
                                finish_mode, &status);
  XzUnpacker_End(&p);

  return 0;
}