#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <libical/ical.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(icaltimetype) * 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create two icaltimetype objects from the input data
  icaltimetype start;
  icaltimetype end;
  stream.ConsumeData(&start, sizeof(icaltimetype));
  stream.ConsumeData(&end, sizeof(icaltimetype));

  // Normalize the icaltimetype objects
  start = icaltime_normalize(start);
  end = icaltime_normalize(end);

  // Create a VTIMEZONE component
  icalcomponent *vtz = icalcomponent_new_vtimezone("Europe/London");
  if (vtz == NULL) {
    return 0;
  }

  // Extract the ms_compatible flag
  int ms_compatible = stream.ConsumeBool();

  // Call the function under test
  icaltimezone_truncate_vtimezone(vtz, &start, &end, ms_compatible);

  // Clean up
  icalcomponent_free(vtz);

  return 0;
}