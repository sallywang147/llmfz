#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "draco/src/draco/core/geometry_attribute.h"
#include "draco/src/draco/core/point_attribute.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  draco::PointAttribute point_attribute;
  draco::GeometryAttribute geometry_attribute;
  const int num_values = stream.ConsumeIntegral<int>();
  draco::PointAttribute::DeduplicateTypedValues<int32_t>(&point_attribute,
                                                    &geometry_attribute,
                                                    num_values);
  return 0;
}
```

The issue is that the `DeduplicateTypedValues` function is templated with a type parameter, and the code uses `int` as the type argument. However, the `ConsumeIntegral` function returns a `uint32_t`, which is a different type. This causes a compilation error.

To fix the issue, change the type argument to `int32_t`, which is the same type as `uint32_t`. This will allow the code to compile and run correctly.