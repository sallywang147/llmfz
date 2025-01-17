 #include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <fuzzer/FuzzedDataProvider.h>

#include "b2nd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct b2nd_context_s *context = b2nd_new();
  if (context == NULL) {
    return 0;
  }

  struct b2nd_array_t *array = b2nd_array_new(context);
  if (array == NULL) {
    b2nd_free(context);
    return 0;
  }

  struct b2nd_array_t **array_ptr =
      (struct b2nd_array_t **)malloc(sizeof(struct b2nd_array_t *));
  if (array_ptr == NULL) {
    b2nd_free(context);
    b2nd_array_free(array);
    return 0;
  }

  int ret = b2nd_copy(context, array, array_ptr);
  if (ret != 0) {
    b2nd_free(context);
    b2nd_array_free(array);
    free(array_ptr);
    return 0;
  }

  b2nd_free(context);
  b2nd_array_free(array);
  free(array_ptr);
  return 0;
}