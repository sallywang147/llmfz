#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include "usbredirparser.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct usbredirparser *parser =
      reinterpret_cast<struct usbredirparser *>(stream.ConsumeIntegral<size_t>());
  const size_t data_size = stream.ConsumeIntegral<size_t>();
  struct usb_redir_iso_packet_header *header =
      reinterpret_cast<struct usb_redir_iso_packet_header *>(
          stream.ConsumeIntegral<size_t>());
  std::string data_str = stream.ConsumeRemainingBytesAsString();
  char *data_ptr = data_str.data();
  const int status = stream.ConsumeIntegral<int>();
  usbredirparser_send_interrupt_packet(parser, data_size, header, data_ptr,
                                      status);
  return 0;
}
```

The original code has a build error because the header file `usbredirparser.h` is not wrapped with `extern "C" {}`. This is necessary because the header file is written in C, and the C++ compiler needs to be told that it should be treated as a C header file.

To fix the error, we need to wrap the `#include "usbredirparser.h"` directive with `extern "C" {}`. The corrected code is shown above.