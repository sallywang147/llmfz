#include <fuzzer/FuzzedDataProvider.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <libraw/libraw.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  LibRaw raw;
  std::exception *stream_exception = nullptr;

  std::string filename = stream.ConsumeRandomLengthString(1024);
  int ret = raw.libraw_openfile_tail(&raw, &stream_exception, filename.c_str());

  if (ret == LIBRAW_SUCCESS) {
    raw.libraw_close(&raw);
  }

  return 0;
}
```

The fixed code includes the necessary headers and wraps the `libraw.h` header with `extern "C" {}`. This should resolve the build error and allow the code to compile successfully.