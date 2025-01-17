#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <libical/ical.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  size_t size1 = stream.ConsumeIntegralInRange<size_t>(0, size-2);
  size_t size2 = stream.ConsumeIntegralInRange<size_t>(0, size-size1-1);
  size_t size3 = size - size1 - size2;

  std::string ical_string1 = stream.ConsumeBytesAsString(size1);
  std::string ical_string2 = stream.ConsumeBytesAsString(size2);
  std::string ical_string3 = stream.ConsumeBytesAsString(size3);

  icalcomponent *ical1 = icalcomponent_new_from_string(ical_string1.c_str());
  icalcomponent *ical2 = icalcomponent_new_from_string(ical_string2.c_str());

  if (ical1 != NULL && ical2 != NULL) {
    struct _icalarray *tzids_to_rename = icalarray_new(sizeof(icaltimezone*), 10);
    icaltimezone *tz = icaltimezone_new();
    icaltimezone_set_tzid(tz, ical_string3.c_str());
    icalarray_append(tzids_to_rename, tz);

    icalcomponent_merge_vtimezone(ical1, ical2, tzids_to_rename);

    icaltimezone_free(tz, 1);
    icalarray_free(tzids_to_rename);
  }

  icalcomponent_free(ical1);
  icalcomponent_free(ical2);

  return 0;
}