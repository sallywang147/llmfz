#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "usbredirparser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the usbredirparser
  struct usbredirparser *parser = usbredirparser_init(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
  if (!parser) {
    return 0;
  }

  // Consume data for the endpoint
  size_t endpoint = stream.ConsumeIntegral<size_t>();

  // Consume data for the usb_redir_iso_packet_header
  struct usb_redir_iso_packet_header packet_header;
  packet_header.endpoint = stream.ConsumeIntegral<uint8_t>();
  packet_header.length = stream.ConsumeIntegral<uint32_t>();
  packet_header.status = stream.ConsumeIntegral<uint32_t>();

  // Consume data for the data buffer
  size_t data_length = stream.remaining_bytes() / 2;
  std::string data_buffer = stream.ConsumeBytesAsString(data_length);
  
  // Consume data for the length
  int length = stream.ConsumeIntegral<int>();

  // Call the function under test
  usbredirparser_send_interrupt_packet(parser, endpoint, &packet_header, data_buffer.data(), length);

  // Clean up
  usbredirparser_free(parser);

  return 0;
}