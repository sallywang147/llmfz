#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "usbredirparser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct usbredirparser *parser = usbredirparser_init(NULL, NULL, NULL, NULL, NULL, NULL);
  if (!parser) {
    return 0;
  }

  size_t length = stream.ConsumeIntegral<size_t>();
  struct usb_redir_start_bulk_receiving_header bulk_receiving_header;
  char *buffer = NULL;
  int status = 0;

  if (stream.remaining_bytes() > 0) {
    buffer = reinterpret_cast<char *>(stream.ConsumeRemainingBytes().data());
    status = stream.ConsumeIntegral<int>();
  }

  usbredirparser_send_buffered_bulk_packet(parser, length, &bulk_receiving_header, buffer, status);

  usbredirparser_destroy(parser);

  return 0;
}