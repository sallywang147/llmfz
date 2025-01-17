#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "usbredirparser.h"

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