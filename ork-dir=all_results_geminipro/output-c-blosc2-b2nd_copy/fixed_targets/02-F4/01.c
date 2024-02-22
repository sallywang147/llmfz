#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "b2nd.h"

extern "C" {
#include "b2nd_array.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  b2nd_context_s* context = b2nd_init();
  if (context == nullptr) {
    return 0;
  }

  b2nd_array_t* array = b2nd_array_new(context);
  if (array == nullptr) {
    b2nd_destroy(context);
    return 0;
  }

  b2nd_array_t::b2nd_array_161** array_161 = nullptr;
  int result = b2nd_copy(context, array, &array_161);
  if (result != 0) {
    b2nd_array_delete(array);
    b2nd_destroy(context);
    return 0;
  }

  b2nd_array_delete(array);  // Fix: Delete the array pointer instead of array_161
  b2nd_destroy(context);
  return 0;
}
```

The issue was that the code was attempting to delete the `array_161` pointer instead of the `array` pointer. This would lead to a runtime error. The fix is to change the line `b2nd_array_delete(array_161);` to `b2nd_array_delete(array);`.