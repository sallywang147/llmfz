#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <libical/ical.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Create a icalcomponent from the fuzzed data
  std::string ical_string1 = provider.ConsumeRandomLengthString();
  icalcomponent *ical1 = icalcomponent_new_from_string(ical_string1.c_str());
  if (ical1 == NULL) {
    return 0;
  }

  // Create a vtimezone component from the fuzzed data
  std::string ical_string2 = provider.ConsumeRemainingBytesAsString();
  icalcomponent *vtimezone = icalcomponent_new_from_string(ical_string2.c_str());
  if (vtimezone == NULL) {
    icalcomponent_free(ical1);
    return 0;
  }

  // Create a tzid property
  icalproperty *tzid_prop = icalproperty_new_tzid("fuzzed_tzid");
  if (tzid_prop == NULL) {
    icalcomponent_free(ical1);
    icalcomponent_free(vtimezone);
    return 0;
  }

  // Create a tzid string
  char tzid[] = "fuzzed_tzid";

  // Create a tzids_to_rename array
  struct _icalarray *tzids_to_rename = icalarray_new(sizeof(icaltimezone*), 10);
  if (tzids_to_rename == NULL) {
    icalcomponent_free(ical1);
    icalcomponent_free(vtimezone);
    icalproperty_free(tzid_prop);
    return 0;
  }

  icalcomponent_handle_conflicting_vtimezones(ical1, vtimezone, tzid_prop, tzid, tzids_to_rename);

  icalcomponent_free(ical1);
  icalcomponent_free(vtimezone);
  icalproperty_free(tzid_prop);
  icalarray_free(tzids_to_rename);

  return 0;
}