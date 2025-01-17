#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *ical_string1 = (char *)malloc(size + 1);
  memcpy(ical_string1, data, size);
  ical_string1[size] = '\0';

  icalcomponent *ical1 = icalcomponent_new_from_string(ical_string1);
  if (ical1 != NULL) {
    icalrecurrencetype *recurrence = icalcomponent_get_recurrence(ical1);
    if (recurrence != NULL) {
      struct icaltimetype start;
      struct icaltimetype end;
      icaltime_from_string("19700101T000000", &start);
      icaltime_from_string("20201231T235959", &end);

      icalcomponent_foreach_recurrence(ical1, &start, &end, NULL, NULL);
    }
  }
  icalcomponent_free(ical1);
  free(ical_string1);

  return 0;
}