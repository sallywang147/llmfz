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

  size_t size1 = stream.ConsumeIntegralInRange<size_t>(1, size - 1);
  size_t size2 = size - size1;

  char *ical_string1 = (char *)malloc(size1 + 1);
  memcpy(ical_string1, data, size1);
  ical_string1[size1] = '\0';

  char *ical_string2 = (char *)malloc(size2 + 1);
  memcpy(ical_string2, data + size1, size2);
  ical_string2[size2] = '\0';

  icalcomponent *ical1 = icalcomponent_new_from_string(ical_string1);
  icalcomponent *ical2 = icalcomponent_new_from_string(ical_string2);

  if (ical1 != NULL && ical2 != NULL) {
    icalcomponent_merge_component(ical1, ical2);
  }

  icalcomponent_free(ical1);
  icalcomponent_free(ical2);

  free(ical_string1);
  free(ical_string2);

  return 0;
}