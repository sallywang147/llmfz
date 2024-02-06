#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "b2nd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t slate_width = stream.ConsumeIntegral<uint8_t>();
  const uint8_t slate_height = stream.ConsumeIntegral<uint8_t>();
  struct b2nd_context_s* slate_image = b2nd_new_context(slate_width, slate_height);
  if (slate_image == nullptr) {
    return 0;
  }

  struct b2nd_array_t* slate_array = b2nd_new_array(slate_width, slate_height);
  if (slate_array == nullptr) {
    b2nd_delete_context(slate_image);
    return 0;
  }

  struct b2nd_array_t::b2nd_array_161** slate_array_161 =
      (struct b2nd_array_t::b2nd_array_161**)malloc(
          sizeof(struct b2nd_array_t::b2nd_array_161*));
  if (slate_array_161 == nullptr) {
    b2nd_delete_array(slate_array);
    b2nd_delete_context(slate_image);
    return 0;
  }

  int result = b2nd_copy(slate_image, slate_array, slate_array_161);
  b2nd_delete_array(slate_array);
  b2nd_delete_context(slate_image);
  free(slate_array_161);

  return result;
}