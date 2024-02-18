#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gpsd.h"

extern "C" {
#include "ubx.h"
}

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) { // gpsd/tests//test_packet.c
  if (size < 10 || size > 9216) {
    return 0;
  }

  struct gps_device_t device;
  memset(&device, 0, sizeof(device));
  device.lexer.state = GPS_WAITING;

  std::vector<char> input_buffer(size);
  memcpy(input_buffer.data(), data, size);
  size_t parsed = ubx_parse(&device, input_buffer.data(), size);
  return parsed;
}