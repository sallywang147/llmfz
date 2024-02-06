#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" {
#include "zstd_errors.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ZSTD_CCtx* const cctx = ZSTD_createCCtx();
  if (!cctx) {
    return 0;
  }

  std::vector<ZSTD_Sequence> sequences;
  while (stream.remaining_bytes() > 0) {
    size_t const seq_size =
        stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
    auto const seq_data = stream.ConsumeBytes<char>(seq_size);
    sequences.emplace_back(seq_data.data(), seq_size);
  }

  size_t const generated_size =
      ZSTD_generateSequences(cctx, sequences.data(), sequences.size(), nullptr, 0);
  if (ZSTD_isError(generated_size)) {
    return 0;
  }

  std::vector<char> generated_buffer(generated_size);
  ZSTD_generateSequences(cctx, sequences.data(), sequences.size(),
                        generated_buffer.data(), generated_buffer.size());

  ZSTD_freeCCtx(cctx);
  return 0;
}
```

The error message is:

```
error: undefined reference to `ZSTD_isError'
```

This error is because the header `zstd_errors.h` is not included. To fix this, add the following line to the top of the file:

```
#include "zstd_errors.h"
```

and wrap it with `extern "C" {}` as follows:

```
extern "C" {
#include "zstd_errors.h"
}
```

This will allow the linker to find the definition of `ZSTD_isError`.