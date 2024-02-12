#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "event2/event.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Event base and event.
  struct event_base* base = event_base_new();
  struct event ev;
  event_assign(&ev, base, -1, EV_READ | EV_PERSIST, nullptr, nullptr);

  // Set up the timeout.
  const time_t timeout_seconds = stream.ConsumeIntegralInRange<time_t>(0, 10);
  const time_t timeout_microseconds =
      stream.ConsumeIntegralInRange<time_t>(0, 1000000);
  struct timeval timeout = {timeout_seconds, timeout_microseconds};

  // Set up the event base.
  event_base_set(base, &ev);

  // Run the event loop.
  event_base_loop(base, EVLOOP_ONCE | EVLOOP_NONBLOCK);

  // Clean up.
  event_base_free(base);

  return 0;
}