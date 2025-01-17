#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <libical/ical.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Divide the input data into two parts for two ical components
  size_t size1 = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::string ical_string1 = stream.ConsumeBytesAsString(size1);
  std::string ical_string2 = stream.ConsumeRemainingBytesAsString();

  icalcomponent *ical1 = icalcomponent_new_from_string(ical_string1.c_str());
  icalcomponent *ical2 = icalcomponent_new_from_string(ical_string2.c_str());

  if (ical1 != NULL && ical2 != NULL) {
    struct _icalarray *tzids_to_rename = icalarray_new(sizeof(char*), 10);
    // Merge the two components
    icalcomponent_merge_vtimezone(ical1, ical2, tzids_to_rename);
    icalarray_free(tzids_to_rename);
  }

  icalcomponent_free(ical1);
  icalcomponent_free(ical2);

  return 0;
}