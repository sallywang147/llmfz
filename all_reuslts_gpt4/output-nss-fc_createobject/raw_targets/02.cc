#include <fuzzer/FuzzedDataProvider.h>
#include "pkcs11.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t session = stream.ConsumeIntegral<size_t>();
  size_t count = stream.ConsumeIntegral<size_t>();
  size_t object = 0;

  // Prepare the CK_ATTRIBUTE array
  CK_ATTRIBUTE_PTR attributes = nullptr;
  if (count > 0) {
    attributes = new CK_ATTRIBUTE[count];
    for (size_t i = 0; i < count; ++i) {
      attributes[i].type = stream.ConsumeIntegral<CK_ATTRIBUTE_TYPE>();
      attributes[i].pValue = const_cast<uint8_t *>(stream.ConsumeRemainingBytes<uint8_t>().data());
      attributes[i].ulValueLen = stream.remaining_bytes();
    }
  }

  FC_CreateObject(session, attributes, count, &object);

  delete[] attributes;

  return 0;
}