#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <libical/ical.h>
#include <fuzzer/FuzzedDataProvider.h>

typedef void (*func_type)(struct icaltime_span * span, void * data);

void callback(struct icaltime_span * span, void * data) {
  // Do nothing.
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char *ical_string1 = (char *)malloc(size + 1);
  memcpy(ical_string1, data, size);
  ical_string1[size] = '\0';

  icalcomponent *ical1 = icalcomponent_new_from_string(ical_string1);
  if (ical1 != NULL) {
    struct icaltimetype start;
    struct icaltimetype end;

    start.year = stream.ConsumeIntegralInRange<int16_t>(1970, 2100);
    start.month = stream.ConsumeIntegralInRange<int16_t>(1, 12);
    start.day = stream.ConsumeIntegralInRange<int16_t>(1, 31);
    start.hour = stream.ConsumeIntegralInRange<int16_t>(0, 23);
    start.minute = stream.ConsumeIntegralInRange<int16_t>(0, 59);
    start.second = stream.ConsumeIntegralInRange<int16_t>(0, 59);

    end.year = stream.ConsumeIntegralInRange<int16_t>(1970, 2100);
    end.month = stream.ConsumeIntegralInRange<int16_t>(1, 12);
    end.day = stream.ConsumeIntegralInRange<int16_t>(1, 31);
    end.hour = stream.ConsumeIntegralInRange<int16_t>(0, 23);
    end.minute = stream.ConsumeIntegralInRange<int16_t>(0, 59);
    end.second = stream.ConsumeIntegralInRange<int16_t>(0, 59);

    icalcomponent_foreach_recurrence(ical1, &start, &end, callback, NULL);
  }
  icalcomponent_free(ical1);
  free(ical_string1);

  return 0;
}