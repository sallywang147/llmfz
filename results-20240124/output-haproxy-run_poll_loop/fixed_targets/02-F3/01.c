#include <fuzzer/FuzzedDataProvider.h>
#include <algorithm>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <vector>

extern "C" {
#include "event2/event.h"
#include "event2/event_struct.h"
#include "event2/event_compat.h"
#include "event2/util.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::vector<struct event*> events;
  std::vector<struct event_base*> bases;
  std::list<struct event*> active_events;
  for (int i = 0; i < stream.ConsumeIntegralInRange<int>(0, 100); i++) {
    struct event_base* base = event_base_new();
    bases.push_back(base);
    struct event* ev = event_new(base, -1, EV_READ | EV_PERSIST, [](evutil_socket_t fd, short what, void* arg) {
      std::list<struct event*>* active_events = (std::list<struct event*>*)arg;
      active_events->remove((struct event*)arg);
    }, &active_events);
    event_add(ev, nullptr);
    events.push_back(ev);
    active_events.push_back(ev);
  }

  for (struct event* ev : events) {
    event_active(ev, 0, 0);
  }

  run_poll_loop(bases[0]);

  for (struct event_base* base : bases) {
    event_base_free(base);
  }
  return 0;
}