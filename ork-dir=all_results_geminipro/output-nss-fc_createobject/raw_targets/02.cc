#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" size_t FC_CreateObject(size_t, struct CK_ATTRIBUTE*, size_t, size_t*);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  size_t num_attributes = provider.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<CK_ATTRIBUTE> attributes(num_attributes);
  for (size_t i = 0; i < num_attributes; i++) {
    attributes[i].type = provider.ConsumeIntegral<CK_ATTRIBUTE_TYPE>();
    attributes[i].pValue = provider.ConsumeBytes<uint8_t>(provider.ConsumeIntegralInRange<size_t>(0, 100)).data();
    attributes[i].ulValueLen = provider.ConsumeIntegral<CK_ULONG>();
  }

  size_t object_handle;
  size_t num_created;
  FC_CreateObject(0, attributes.data(), num_attributes, &num_created);

  return 0;
}