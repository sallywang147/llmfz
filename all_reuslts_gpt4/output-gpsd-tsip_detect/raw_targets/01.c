#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gps.h"

struct gps_device_t device;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize the gps_device_t struct
  device.context = nullptr;
  device.device_type = nullptr;
  device.device_name = nullptr;
  device.observed = 0;
  device.sourcename = nullptr;
  device.gpsdata.online = stream.ConsumeBool();
  device.gpsdata.fix.mode = stream.ConsumeIntegralInRange<int>(MODE_NOT_SEEN, MODE_3D);
  device.gpsdata.fix.status = stream.ConsumeIntegralInRange<int>(STATUS_NO_FIX, STATUS_DGPS_FIX);
  device.gpsdata.satellites_used = stream.ConsumeIntegralInRange<int>(0, MAXCHANNELS);
  device.gpsdata.dop.pdop = stream.ConsumeFloatingPoint<double>();
  device.gpsdata.dop.hdop = stream.ConsumeFloatingPoint<double>();
  device.gpsdata.dop.vdop = stream.ConsumeFloatingPoint<double>();
  device.gpsdata.dop.tdop = stream.ConsumeFloatingPoint<double>();
  device.gpsdata.dop.gdop = stream.ConsumeFloatingPoint<double>();
  device.gpsdata.dop.xdop = stream.ConsumeFloatingPoint<double>();
  device.gpsdata.dop.ydop = stream.ConsumeFloatingPoint<double>();
  device.gpsdata.fix.time = stream.ConsumeFloatingPoint<double>();
  device.gpsdata.fix.latitude = stream.ConsumeFloatingPointInRange<double>(-90.0, 90.0);
  device.gpsdata.fix.longitude = stream.ConsumeFloatingPointInRange<double>(-180.0, 180.0);
  device.gpsdata.fix.altitude = stream.ConsumeFloatingPoint<double>();
  device.gpsdata.fix.speed = stream.ConsumeFloatingPoint<double>();
  device.gpsdata.fix.track = stream.ConsumeFloatingPoint<double>();
  device.gpsdata.fix.climb = stream.ConsumeFloatingPoint<double>();
  device.gpsdata.fix.epx = stream.ConsumeFloatingPoint<double>();
  device.gpsdata.fix.epy = stream.ConsumeFloatingPoint<double>();
  device.gpsdata.fix.epv = stream.ConsumeFloatingPoint<double>();
  device.gpsdata.fix.eps = stream.ConsumeFloatingPoint<double>();
  device.gpsdata.fix.epd = stream.ConsumeFloatingPoint<double>();
  device.gpsdata.fix.epc = stream.ConsumeFloatingPoint<double>();

  // Call the function to fuzz
  tsip_detect(&device);

  return 0;
}