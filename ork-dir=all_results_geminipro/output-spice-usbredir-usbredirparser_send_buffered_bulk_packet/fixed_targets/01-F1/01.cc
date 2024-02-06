#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "usbredirparser.h"

extern "C" {
#include "usbredirparser.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t buffer_size = stream.ConsumeIntegral<size_t>();
  const struct usb_redir_start_bulk_receiving_header* header =
      reinterpret_cast<const struct usb_redir_start_bulk_receiving_header*>(
          stream.ConsumeBytes<uint8_t>(sizeof(struct usb_redir_start_bulk_receiving_header)).data());
  const std::string buffer = stream.ConsumeRemainingBytesAsString();
  const int result = stream.ConsumeIntegral<int>();

  struct usbredirparser parser;
  usbredirparser_init(&parser);
  usbredirparser_send_buffered_bulk_packet(&parser, buffer_size, header,
                                           const_cast<char*>(buffer.c_str()), result);
  usbredirparser_destroy(&parser);

  return 0;
}