#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "usbredirparser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < sizeof(struct usb_redir_start_bulk_receiving_header)) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  struct usbredirparser *parser = usbredirparser_init(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
  if (parser == NULL) {
    return 0;
  }

  size_t bulk_size = provider.ConsumeIntegral<size_t>();
  struct usb_redir_start_bulk_receiving_header *header = (struct usb_redir_start_bulk_receiving_header*)provider.ConsumeBytes<uint8_t>(sizeof(struct usb_redir_start_bulk_receiving_header)).data();
  std::string bulk_data = provider.ConsumeRemainingBytesAsString();
  int status = provider.ConsumeIntegral<int>();

  usbredirparser_send_buffered_bulk_packet(parser, bulk_size, header, (char*)bulk_data.c_str(), status);

  usbredirparser_destroy(parser);

  return 0;
}