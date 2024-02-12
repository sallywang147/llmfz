#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "ev.h"
#include "ev_config.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  ev_tstamp timeout = stream.ConsumeFloatingPoint<double>();
  ev_loop_t* loop = ev_loop_new(EVFLAG_AUTO);
  ev_timer timer;
  ev_timer_init(&timer, NULL, timeout, 0.);
  ev_timer_start(loop, &timer);
  run_poll_loop(loop);
  ev_timer_stop(loop, &timer);
  ev_loop_destroy(loop);
  return 0;
}