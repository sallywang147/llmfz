#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "usbredirparser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a usbredirparser instance
  struct usbredirparser *parser = usbredirparser_create(NULL, NULL, 0);
  if (!parser) {
    return 0;
  }

  // Consume data from the stream
  size_t endpoint = stream.ConsumeIntegral<size_t>();
  struct usb_redir_iso_packet_header iso_packet_header;
  iso_packet_header.endpoint = stream.ConsumeIntegral<uint32_t>();
  iso_packet_header.length = stream.ConsumeIntegral<uint32_t>();
  iso_packet_header.status = stream.ConsumeIntegral<uint32_t>();
  iso_packet_header.speed = stream.ConsumeIntegral<uint32_t>();
  iso_packet_header.start_frame = stream.ConsumeIntegral<uint32_t>();
  iso_packet_header.number_of_packets = stream.ConsumeIntegral<uint32_t>();
  iso_packet_header.error_count = stream.ConsumeIntegral<uint32_t>();
  int packets = stream.ConsumeIntegral<int>();

  std::string packet_data = stream.ConsumeRemainingBytesAsString();
  char *packet_data_ptr = const_cast<char *>(packet_data.c_str());

  // Call the target function
  usbredirparser_send_iso_packet(parser, endpoint, &iso_packet_header, packet_data_ptr, packets);

  // Clean up
  usbredirparser_destroy(parser);

  return 0;
}