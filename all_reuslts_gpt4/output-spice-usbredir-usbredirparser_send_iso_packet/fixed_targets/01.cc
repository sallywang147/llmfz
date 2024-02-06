#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "usbredirparser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct usbredirparser* parser = usbredirparser_create(nullptr, nullptr, 0);
  if(parser == nullptr) {
    return 0;
  }

  size_t packet_id = stream.ConsumeIntegral<size_t>();
  struct usb_redir_iso_packet_header packet_header;
  packet_header.endpoint = stream.ConsumeIntegral<uint8_t>();
  packet_header.length = stream.ConsumeIntegral<uint16_t>();
  packet_header.status = stream.ConsumeIntegral<uint32_t>();
  packet_header.speed = stream.ConsumeIntegral<uint8_t>();
  packet_header.start_frame = stream.ConsumeIntegral<uint32_t>();
  packet_header.number_of_packets = stream.ConsumeIntegral<uint16_t>();
  packet_header.error_count = stream.ConsumeIntegral<uint16_t>();
  packet_header.pad = stream.ConsumeIntegral<uint16_t>();

  int data_len = stream.ConsumeIntegralInRange<int>(0, stream.remaining_bytes());
  std::string data_str = stream.ConsumeBytesAsString(data_len);

  usbredirparser_send_iso_packet(parser, packet_id, &packet_header, data_str.data(), data_len);

  usbredirparser_destroy(parser);

  return 0;
}