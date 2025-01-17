#include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/core/geometry_attribute.h"
#include "draco/src/draco/core/point_attribute.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::GeometryAttribute geometry_attribute;
  draco::PointAttribute point_attribute;

  FuzzedDataProvider provider(data, size);
  int num_unique_values = provider.ConsumeIntegralInRange<int>(0, 1000);
  for (int i = 0; i < num_unique_values; ++i) {
    geometry_attribute.AddValue(provider.ConsumeIntegral<int>());
  }
  point_attribute.DeduplicateValues(&point_attribute, &geometry_attribute, num_unique_values);

  return 0;
}
```

The fix is to replace `DeduplicateTypedValues` with `DeduplicateValues` in the following line:

```c++
  point_attribute.DeduplicateTypedValues<int>(&point_attribute, &geometry_attribute, num_unique_values);
```

The `DeduplicateTypedValues` method is not a member of the `PointAttribute` class, but `DeduplicateValues` is.