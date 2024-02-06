#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>

struct tusb_control_request_t {
    uint8_t bmRequestType;
    uint8_t bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
};

extern bool netd_control_xfer_cb(char, char, struct tusb_control_request_t *);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char arg1 = stream.ConsumeIntegral<char>();
  char arg2 = stream.ConsumeIntegral<char>();
  
  tusb_control_request_t request;
  if (stream.remaining_bytes() >= sizeof(request)) {
    request.bmRequestType = stream.ConsumeIntegral<uint8_t>();
    request.bRequest = stream.ConsumeIntegral<uint8_t>();
    request.wValue = stream.ConsumeIntegral<uint16_t>();
    request.wIndex = stream.ConsumeIntegral<uint16_t>();
    request.wLength = stream.ConsumeIntegral<uint16_t>();
  } else {
    return 0;
  }

  netd_control_xfer_cb(arg1, arg2, &request);

  return 0;
}