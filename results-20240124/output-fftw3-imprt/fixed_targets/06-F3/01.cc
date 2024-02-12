#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "planner.h"
#include "scanner.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct planner_s ego;
  struct scanner_s sc;

  ego.n_events = stream.ConsumeIntegral<int>();
  ego.events = new event[ego.n_events];
  for (int i = 0; i < ego.n_events; i++) {
    ego.events[i].type = stream.ConsumeIntegral<int>();
    ego.events[i].time = stream.ConsumeIntegral<int>();
    ego.events[i].data = stream.ConsumeIntegral<int>();
  }
  ego.start_time = stream.ConsumeIntegral<int>();
  ego.end_time = stream.ConsumeIntegral<int>();
  ego.n_states = stream.ConsumeIntegral<int>();
  ego.states = new state[ego.n_states];
  for (int i = 0; i < ego.n_states; i++) {
    ego.states[i].type = stream.ConsumeIntegral<int>();
    ego.states[i].time = stream.ConsumeIntegral<int>();
    ego.states[i].data = stream.ConsumeIntegral<int>();
  }
  ego.n_actions = stream.ConsumeIntegral<int>();
  ego.actions = new action[ego.n_actions];
  for (int i = 0; i < ego.n_actions; i++) {
    ego.actions[i].type = stream.ConsumeIntegral<int>();
    ego.actions[i].time = stream.ConsumeIntegral<int>();
    ego.actions[i].data = stream.ConsumeIntegral<int>();
  }
  ego.n_observations = stream.ConsumeIntegral<int>();
  ego.observations = new observation[ego.n_observations];
  for (int i = 0; i < ego.n_observations; i++) {
    ego.observations[i].type = stream.ConsumeIntegral<int>();
    ego.observations[i].time = stream.ConsumeIntegral<int>();
    ego.observations[i].data = stream.ConsumeIntegral<int>();
  }

  sc.n_events = stream.ConsumeIntegral<int>();
  sc.events = new event[sc.n_events];
  for (int i = 0; i < sc.n_events; i++) {
    sc.events[i].type = stream.ConsumeIntegral<int>();
    sc.events[i].time = stream.ConsumeIntegral<int>();
    sc.events[i].data = stream.ConsumeIntegral<int>();
  }
  sc.start_time = stream.ConsumeIntegral<int>();
  sc.end_time = stream.ConsumeIntegral<int>();
  sc.n_states = stream.ConsumeIntegral<int>();
  sc.states = new state[sc.n_states];
  for (int i = 0; i < sc.n_states; i++) {
    sc.states[i].type = stream.ConsumeIntegral<int>();
    sc.states[i].time = stream.ConsumeIntegral<int>();
    sc.states[i].data = stream.ConsumeIntegral<int>();
  }
  sc.n_actions = stream.ConsumeIntegral<int>();
  sc.actions = new action[sc.n_actions];
  for (int i = 0; i < sc.n_actions; i++) {
    sc.actions[i].type = stream.ConsumeIntegral<int>();
    sc.actions[i].time = stream.ConsumeIntegral<int>();
    sc.actions[i].data = stream.ConsumeIntegral<int>();
  }
  sc.n_observations = stream.ConsumeIntegral<int>();
  sc.observations = new observation[sc.n_observations];
  for (int i = 0; i < sc.n_observations; i++) {
    sc.observations[i].type = stream.ConsumeIntegral<int>();
    sc.observations[i].time = stream.ConsumeIntegral<int>();
    sc.observations[i].data = stream.ConsumeIntegral<int>();
  }

  imprt(&ego, &sc);

  return 0;
}