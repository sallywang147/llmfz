#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <libical/ical.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" void callback(struct icalcomponent *comp, struct icaltime_span *span, void *data) {
  // Callback function does nothing for now.
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data to create a string for the icalcomponent
  std::string str = stream.ConsumeBytesAsString(stream.remaining_bytes());
  char *ical_string = strdup(str.c_str());

  // Create icalcomponent from the string
  icalcomponent *ical = icalcomponent_new_from_string(ical_string);
  if (ical != NULL) {
    // Create start and end times
    struct icaltimetype start = icaltime_from_timet_with_zone(time(NULL), 0, NULL);
    struct icaltimetype end = icaltime_from_timet_with_zone(time(NULL) + 86400, 0, NULL);

    // Call the function to fuzz
    icalcomponent_foreach_recurrence(ical, &start, &end, callback, NULL);
  }

  // Clean up
  icalcomponent_free(ical);
  free(ical_string);

  return 0;
}