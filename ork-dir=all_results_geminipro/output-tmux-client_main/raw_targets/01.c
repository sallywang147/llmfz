#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "event2/event.h"
#include "event2/util.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct event_base* base = event_base_new();
  FuzzedDataProvider provider(data, size);

  // Generate random arguments for client_main.
  int argc = provider.ConsumeIntegralInRange<int>(1, 10);
  std::vector<char*> argv(argc);
  for (int i = 0; i < argc; i++) {
    size_t arg_size = provider.ConsumeIntegralInRange<size_t>(0, 100);
    argv[i] = new char[arg_size + 1];
    provider.ConsumeBytes(argv[i], arg_size);
    argv[i][arg_size] = '\0';
  }

  // Generate random flags and feat.
  size_t flags = provider.ConsumeIntegral<size_t>();
  int feat = provider.ConsumeIntegral<int>();

  // Call client_main with the generated arguments.
  int ret = client_main(base, argc, argv.data(), flags, feat);

  // Clean up.
  for (int i = 0; i < argc; i++) {
    delete[] argv[i];
  }
  event_base_free(base);

  return ret;
}