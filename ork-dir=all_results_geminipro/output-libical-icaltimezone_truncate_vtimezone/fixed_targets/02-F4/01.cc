#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *ical_string1 = (char *)malloc(size + 1);
  memcpy(ical_string1, data, size);
  ical_string1[size] = '\0';

  icalcomponent *ical1 = icalcomponent_new_from_string(ical_string1);
  if (ical1 != NULL) {
    icaltimetype start = {};
    icaltimetype end = {};
    icaltimezone_truncate_vtimezone(ical1, &start, &end, 0);
    icalcomponent_free(ical1); // Free the icalcomponent before freeing the string.
  }
  free(ical_string1);

  return 0;
}