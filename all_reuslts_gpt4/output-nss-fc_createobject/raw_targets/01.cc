#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t session = stream.ConsumeIntegral<size_t>();
  size_t count = stream.ConsumeIntegral<size_t>();
  size_t object = 0;
  
  std::vector<CK_ATTRIBUTE> attributes;
  for (size_t i = 0; i < count; ++i) {
    CK_ATTRIBUTE attribute;
    attribute.type = stream.ConsumeIntegral<CK_ATTRIBUTE_TYPE>();
    attribute.pValue = const_cast<void*>(static_cast<const void*>(stream.ConsumeRandomLengthString().c_str()));
    attribute.ulValueLen = stream.ConsumeIntegral<CK_ULONG>();
    attributes.push_back(attribute);
  }

  FC_CreateObject(session, attributes.data(), count, &object);

  return 0;
}