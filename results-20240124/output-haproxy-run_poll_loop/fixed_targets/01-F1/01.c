#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t num_threads = stream.ConsumeIntegral<uint8_t>();
  const uint8_t num_fds = stream.ConsumeIntegral<uint8_t>();
  const uint8_t num_events = stream.ConsumeIntegral<uint8_t>();
  const uint8_t num_timers = stream.ConsumeIntegral<uint8_t>();
  const uint8_t num_loops = stream.ConsumeIntegral<uint8_t>();
  const uint8_t num_calls = stream.ConsumeIntegral<uint8_t>();

  // Create a fake poll loop.
  std::vector<int> fds;
  std::vector<void*> events;
  std::vector<void*> timers;
  for (uint8_t i = 0; i < num_fds; i++) {
    fds.push_back(stream.ConsumeIntegral<int>());
  }
  for (uint8_t i = 0; i < num_events; i++) {
    events.push_back(stream.ConsumeIntegral<void*>());
  }
  for (uint8_t i = 0; i < num_timers; i++) {
    timers.push_back(stream.ConsumeIntegral<void*>());
  }

  // Run the poll loop.
  for (uint8_t i = 0; i < num_loops; i++) {
    for (uint8_t j = 0; j < num_calls; j++) {
      run_poll_loop();
    }
  }

  return 0;
}