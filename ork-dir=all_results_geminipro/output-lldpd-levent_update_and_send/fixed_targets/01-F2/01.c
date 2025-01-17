#include <fuzzer/FuzzedDataProvider.h>
#include <libevent/event.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  int fd = provider.ConsumeIntegral<int>();
  short what = provider.ConsumeIntegral<short>();
  std::string arg = provider.ConsumeRemainingBytesAsString();

  event_base* base = event_base_new();
  event* ev = event_new(base, fd, what, levent_update_and_send, const_cast<char*>(arg.c_str()));
  event_add(ev, nullptr);
  event_base_dispatch(base);

  return 0;
}