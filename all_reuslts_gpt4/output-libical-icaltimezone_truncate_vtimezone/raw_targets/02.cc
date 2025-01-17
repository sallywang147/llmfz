#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <libical/ical.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider fuzzed_data(data, size);

  char *ical_string = (char *)malloc(size + 1);
  memcpy(ical_string, data, size);
  ical_string[size] = '\0';

  icalcomponent *vtz = icalcomponent_new_from_string(ical_string);
  if (vtz != NULL) {
    icaltimetype start = icaltime_from_timet_with_zone(fuzzed_data.ConsumeIntegral<time_t>(), fuzzed_data.ConsumeBool(), NULL);
    icaltimetype end = icaltime_from_timet_with_zone(fuzzed_data.ConsumeIntegral<time_t>(), fuzzed_data.ConsumeBool(), NULL);

    icaltimezone_truncate_vtimezone(vtz, &start, &end, fuzzed_data.ConsumeBool());
  }
  icalcomponent_free(vtz);
  free(ical_string);

  return 0;
}