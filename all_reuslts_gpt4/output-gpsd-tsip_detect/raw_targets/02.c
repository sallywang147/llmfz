#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gpsd/gpsd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct gps_device_t device;
  memset(&device, 0, sizeof(device));

  FuzzedDataProvider provider(data, size);
  const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
      0,
      provider.remaining_bytes());
  auto next_input = provider.ConsumeBytes<unsigned char>(next_size);
  memcpy(device.gpsdata.packet.outbuffer, next_input.data(), next_input.size());
  device.gpsdata.packet.outbuflen = next_input.size();

  tsip_detect(&device);

  return 0;
}