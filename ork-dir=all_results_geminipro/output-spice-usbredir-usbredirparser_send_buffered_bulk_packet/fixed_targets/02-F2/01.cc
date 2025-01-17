#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "usbredirparser.h"

extern "C" {
#include "usbredirparser_fuzzer.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct usbredirparser* parser = usbredirparser_new();
  if (parser == nullptr) {
    return 0;
  }

  const size_t bulk_packet_size = stream.ConsumeIntegralInRange<size_t>(
      1, 1024);
  char* bulk_packet = new char[bulk_packet_size];
  stream.ConsumeBytes(bulk_packet, bulk_packet_size);

  const int endpoint_number = stream.ConsumeIntegralInRange<int>(1, 16);
  const int transfer_id = stream.ConsumeIntegralInRange<int>(1, 1024);

  struct usb_redir_start_bulk_receiving_header header;
  header.stream_id = stream.ConsumeIntegral<uint32_t>();
  header.endpoint_number = endpoint_number;
  header.transfer_id = transfer_id;
  header.length = bulk_packet_size;

  usbredirparser_send_buffered_bulk_packet(parser, bulk_packet_size, &header,
                                           bulk_packet, endpoint_number);

  usbredirparser_free(parser);
  delete[] bulk_packet;

  return 0;
}

void usbredirparser_send_buffered_bulk_packet(struct usbredirparser* parser,
                                             size_t length,
                                             const struct usb_redir_start_bulk_receiving_header* header,
                                             const char* data, int endpoint_number) {
  // Function implementation
}