#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" size_t FC_CreateObject(size_t, struct CK_ATTRIBUTE*, size_t, size_t*);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  size_t object_class = provider.ConsumeIntegralInRange<size_t>(0, 1000);
  size_t attribute_count = provider.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<CK_ATTRIBUTE> attributes(attribute_count);
  for (auto& attribute : attributes) {
    attribute.type = provider.ConsumeIntegralInRange<CK_ATTRIBUTE_TYPE>(0, 100);
    attribute.pValue = provider.ConsumeBytes<uint8_t>(
        provider.ConsumeIntegralInRange<size_t>(0, 1000));
    attribute.ulValueLen = attribute.pValue.size();
  }
  size_t object_handle;
  FC_CreateObject(object_class, attributes.data(), attribute_count, &object_handle);
  return 0;
}