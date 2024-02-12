#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "avahi-common/defs.h"
#include "avahi-common/error.h"
#include "avahi-common/malloc.h"
extern "C" {
#include "avahi-common/string.h"
#include "avahi-common/thread-watch.h"
#include "avahi-common/timeval.h"
#include "avahi-core/core.h"
#include "avahi-core/error.h"
#include "avahi-core/string-list.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    avahi_set_allocator(avahi_malloc, avahi_free);
    avahi_set_error_handler(nullptr);
    avahi_set_thread_watch_callback(nullptr);
    avahi_set_log_level(AVA_LOG_LEVEL_INFO);
    initialized = true;
  }
  struct AvahiStringList *list = avahi_string_list_new();
  if (!list) {
    return 0;
  }
  FuzzedDataProvider provider(data, size);
  const size_t max_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<char> buffer(max_size);
  provider.ConsumeBytes<char>(buffer.data(), buffer.size());
  avahi_string_list_add_printf(list, buffer.data());
  avahi_string_list_free(list);
  return 0;
}