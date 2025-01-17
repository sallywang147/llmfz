 #include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fuzzer/FuzzedDataProvider.h>

#include "b2nd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  struct b2nd_context_s* b2nd_ctx = b2nd_init();
  if (b2nd_ctx == NULL) {
    return 0;
  }

  struct b2nd_array_t* b2nd_arr = b2nd_create_array(b2nd_ctx);
  if (b2nd_arr == NULL) {
    b2nd_destroy(b2nd_ctx);
    return 0;
  }

  struct b2nd_array_t.161** b2nd_arr_ptr =
      (struct b2nd_array_t.161**)malloc(sizeof(struct b2nd_array_t.161*));
  if (b2nd_arr_ptr == NULL) {
    b2nd_destroy_array(b2nd_arr);
    b2nd_destroy(b2nd_ctx);
    return 0;
  }

  int ret = b2nd_copy(b2nd_ctx, b2nd_arr, b2nd_arr_ptr);
  if (ret != 0) {
    printf("b2nd_copy failed with error code %d\n", ret);
  }

  free(b2nd_arr_ptr);
  b2nd_destroy_array(b2nd_arr);
  b2nd_destroy(b2nd_ctx);
  return 0;
}