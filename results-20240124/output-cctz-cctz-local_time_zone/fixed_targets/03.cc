#include <cctz/time_zone.h>
#include <cctz/time_zone_registry.h>

extern "C" {
#include <cctz/civil_time.h>
#include <cctz/time_zone.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  cctz::time_zone::Impl *local_tz = cctz::local_time_zone();
  cctz::parse(parse_format, date_format, *local_tz, "%Y-%m-%d %H:%M:%S");
  return 0;
}