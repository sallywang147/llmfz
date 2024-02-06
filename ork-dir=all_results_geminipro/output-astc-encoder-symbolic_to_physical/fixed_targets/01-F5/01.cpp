#include "astcenc_internal.h"

#include <array>
#include <fuzzer/FuzzedDataProvider.h>
#include <vector>

struct BlockSizes {
  int x;
  int y;
  int z;
};

std::array<BlockSizes, 3> testSz{{
    {4, 4, 1},   // Highest bitrate
    {12, 12, 1}, // Largest 2D block
    {6, 6, 6}    // Largest 3D block
}};

std::array<block_size_descriptor, 3> testBSD;

extern "C" {
#include "astcenc_core.h"
}

extern "C" bool bsd_initializer() {
  for (int i = 0; i < testSz.size(); i++) {
    init_block_size_descriptor(testSz[i].x, testSz[i].y, testSz[i].z, false, 4, 1.0f, testBSD[i]);
  }

  return true;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Preinitialize the block size descriptors we need
  static bool init = bsd_initializer();

  // Must have 4 (select block size) and 16 (payload) bytes
  if (size < 4 + 16) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Select a block size to test
  int i = stream.ConsumeIntegralInRange<int>(0, testSz.size() - 1);

  // Populate the symbolic block
  symbolic_compressed_block scb;
  std::vector<uint8_t> buffer = stream.ConsumeBytes<uint8_t>(16);
  std::memcpy(scb.data, buffer.data(), 16);

  // Call the function under test
  char pcb[16];
  symbolic_to_physical(testBSD[i], &scb, pcb);

  return 0;
}