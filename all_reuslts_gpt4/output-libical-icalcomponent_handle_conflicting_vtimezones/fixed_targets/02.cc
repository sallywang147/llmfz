#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <libical/ical.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  std::string ical_string = stream.ConsumeRandomLengthString();

  icalcomponent *ical1 = icalcomponent_new_from_string((char *)ical_string.c_str());
  icalcomponent *vtimezone = icalcomponent_new_from_string((char *)ical_string.c_str());
  icalproperty *tzid_prop = icalproperty_new_from_string((char *)ical_string.c_str());
  std::string tzid = stream.ConsumeRandomLengthString();

  struct _icalarray *tzids_to_rename = icalarray_new(sizeof(struct icaltimezone), 10);

  if (ical1 != NULL && vtimezone != NULL && tzid_prop != NULL && tzids_to_rename != NULL) {
    icalcomponent_handle_conflicting_vtimezones(ical1, vtimezone, tzid_prop, (char *)tzid.c_str(), tzids_to_rename);
  }

  icalcomponent_free(ical1);
  icalcomponent_free(vtimezone);
  icalproperty_free(tzid_prop);
  icalarray_free(tzids_to_rename);

  return 0;
}