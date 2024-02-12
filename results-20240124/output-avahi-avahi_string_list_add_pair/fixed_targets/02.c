#include <avahi-common/error.h>
#include <avahi-common/timeval.h>

extern "C" {
#include <avahi-core/string-list.h>
}

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  AvahiStringList* list = avahi_string_list_new();
  avahi_string_list_add_pair(list, "key", "value");
  avahi_string_list_free(list);
  return 0;
}