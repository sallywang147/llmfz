#include "common.h"
#include <fuzzer/FuzzedDataProvider.h>

#ifndef HASHTYPE
#error Macro HASHTYPE must be defined.
#endif

#ifndef FNAME
#error Macro FNAME must be defined.
#endif

#define CONCAT_TYPE(x) _PASTE2(HASHTYPE, x)

#define init CONCAT_TYPE(_init)
#define update CONCAT_TYPE(_update)
#define digest CONCAT_TYPE(_digest)
#define destroy CONCAT_TYPE(_destroy)
#define copy CONCAT_TYPE(_copy)

#define STR(x) #x
#define INCLUDE(x) STR(x)

extern "C" {
#include INCLUDE(FNAME)
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  if (!size)
    return 0;

  FuzzedDataProvider stream(data, size);
  hash_state *hs1;
  if (init(&hs1))
    return 0;

  hash_state *hs2;
  if (init(&hs2))
    goto error1;

  while (stream.remaining_bytes()) {
    size_t num_bytes = stream.ConsumeIntegral<size_t>();
    std::vector<uint8_t> buffer = stream.ConsumeBytes<uint8_t>(num_bytes);

    if (update(hs1, buffer.data(), buffer.size()))
      goto error2;
  }

  copy(hs1, hs2);
  destroy(hs2); // Call destroy on hs2 before error handling

error2:
  destroy(hs1);
error1:
  destroy(hs2);
  return 0;
}
```

The fixed code calls `destroy(hs2);` before the error handling block to ensure that `hs2` is properly destroyed even if an error occurs during the `copy` operation. This resolves the issue reported in the build error message.