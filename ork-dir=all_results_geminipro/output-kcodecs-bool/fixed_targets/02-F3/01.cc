#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <QtCore/qvariant.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  size_t variant_type = provider.ConsumeIntegralInRange<size_t>(0, 10);
  QVariant v(static_cast<QVariant::Type>(variant_type));

  size_t value_size = provider.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<uint8_t> value_buffer(value_size);
  provider.ConsumeBytes<uint8_t>(value_buffer.data(), value_size);

  size_t name_size = provider.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<uint8_t> name_buffer(name_size);
  provider.ConsumeBytes<uint8_t>(name_buffer.data(), name_size);

  bool ret = v.toVariantData(static_cast<int>(variant_type), value_buffer.data(),
                             value_size, name_buffer.data(), name_size);
  (void)ret;  // avoid unused variable warning

  return 0;
}