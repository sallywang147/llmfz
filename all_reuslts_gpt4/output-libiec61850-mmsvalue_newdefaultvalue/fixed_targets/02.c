#include <fuzzer/FuzzedDataProvider.h>
#include "iec61850_server.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create an MmsVariableSpecification object
  MmsVariableSpecification typeSpec;
  typeSpec.name = stream.ConsumeRandomLengthString().c_str();
  typeSpec.type = (MmsType)stream.ConsumeIntegralInRange<int>(MMS_ARRAY, MMS_UTC_TIME);
  typeSpec.structure.elementCount = stream.ConsumeIntegral<int>();
  typeSpec.structure.elements = NULL; // The elements array is not used in this function

  // Call the function to fuzz
  MmsValue* value = MmsValue_newDefaultValue(&typeSpec);

  // Clean up
  if (value != NULL) {
    MmsValue_delete(value);
  }

  return 0;
}