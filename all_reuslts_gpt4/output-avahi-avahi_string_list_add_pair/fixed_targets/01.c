#include <fuzzer/FuzzedDataProvider.h>
#include <avahi-common/strlst.h>

#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize an empty AvahiStringList
  struct AvahiStringList *list = NULL;

  // Loop until we've consumed all the data
  while (stream.remaining_bytes() > 0) {
    // Generate a key-value pair from the data
    std::string key = stream.ConsumeRandomLengthString();
    std::string value = stream.ConsumeRandomLengthString();

    // Add the key-value pair to the list
    list = avahi_string_list_add_pair(list, key.data(), value.data());
  }

  // Free the list
  avahi_string_list_free(list);

  return 0;
}