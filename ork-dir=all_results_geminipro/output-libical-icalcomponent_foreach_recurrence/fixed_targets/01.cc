#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <libical/ical.h>

extern "C" {
#include <libical/icaltime.h>
#include <libical/icalrecur.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *ical_string1 = (char *)malloc(size + 1);
  memcpy(ical_string1, data, size);
  ical_string1[size] = '\0';

  icalcomponent *ical1 = icalcomponent_new_from_string(ical_string1);
  if (ical1 != NULL) {
    icaltimetype start, end;
    icaltime_init_now(&start);
    icaltime_init_now(&end);
    icalrecur_enumerate(ical1, &start, &end, NULL, NULL);
    icalcomponent_foreach_recurrence(ical1, &start, &end, NULL, NULL);
    icalrecur_enumerate(ical1, &start, &end, NULL, NULL);
    icalcomponent_foreach_recurrence(ical1, &start, &end, NULL, NULL);
  }
  icalcomponent_free(ical1);
  free(ical_string1);

  return 0;
}