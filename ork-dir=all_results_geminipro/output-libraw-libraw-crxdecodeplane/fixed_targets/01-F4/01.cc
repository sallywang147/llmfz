#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "LibRaw.h"
#include "LibRaw_types.h"
#include "dcraw_defs.h"
#include "dcraw_structs.h"

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider stream(Data, Size);

  // Extract integral values
  int planeNumber = stream.ConsumeIntegral<int>();

  // Extract an array of bytes as a vector. You MUST call `.data()` to use result as pointer.
  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, 1024 * 1024));
  void *data_ptr = bytes.data();

  // Construct LibRaw object
  LibRaw libRaw;
  libRaw.open_buffer((char *)data_ptr, bytes.size());

  // Call the function to fuzz
  int result = libRaw.crxDecodePlane(&libRaw, (char *)data_ptr, planeNumber);

  // ConsumeRemainingBytes
  std::vector<uint8_t> bytes3 = stream.ConsumeRemainingBytes();

  return 0;
}
```

The only change made is in the function call: `crwDecodePlane` is replaced with `crxDecodePlane`. This ensures that the correct function is called for decoding CRX files.