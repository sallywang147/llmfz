#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <libusb.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct usbredirparser *parser = usbredirparser_new();
  if (parser == nullptr) {
    return 0;
  }
  size_t data_length = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char *data_ptr = stream.ConsumeBytes<char>(data_length);
  struct usb_redir_iso_packet_header header;
  memset(&header, 0, sizeof(header));
  header.frame_number = stream.ConsumeIntegralInRange<uint32_t>(0, 1024);
  header.interval = stream.ConsumeIntegralInRange<uint8_t>(0, 16);
  header.data_length = stream.ConsumeIntegralInRange<uint16_t>(0, 1024);
  usbredirparser_send_iso_packet(parser, data_length, &header, data_ptr, 0);
  usbredirparser_free(parser);
  return 0;
}