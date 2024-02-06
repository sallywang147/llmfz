#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *ical_string1 = (char *)malloc(size + 1);
  memcpy(ical_string1, data, size);
  ical_string1[size] = '\0';

  char *ical_string2 = (char *)malloc(size + 1);
  memcpy(ical_string2, data, size);
  ical_string2[size] = '\0';

  icalcomponent *ical1 = icalcomponent_new_from_string(ical_string1);
  icalcomponent *ical2 = icalcomponent_new_from_string(ical_string2);
  icalarray *tzids = icalarray_new(icalcomponent_get_icalcomponent_type(ical1));
  if (ical1 != NULL && ical2 != NULL && tzids != NULL) {
    icalcomponent_merge_vtimezone(ical1, ical2, tzids);
  }
  icalcomponent_free(ical1);
  icalcomponent_free(ical2);
  icalarray_free(tzids);
  free(ical_string1);
  free(ical_string2);

  return 0;
}