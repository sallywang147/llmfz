#include <fuzzer/FuzzedDataProvider.h>
#include "iec61850_server.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a MmsVariableSpecification object
  MmsVariableSpecification* typeSpec = (MmsVariableSpecification*) calloc(1, sizeof(MmsVariableSpecification));

  // Set the type of the MmsVariableSpecification object
  typeSpec->type = (MmsType) stream.ConsumeIntegralInRange<int>(MMS_ARRAY, MMS_UTC_TIME);

  // Call the function to fuzz
  MmsValue* value = MmsValue_newDefaultValue(typeSpec);

  // Clean up
  if (value != NULL) {
    MmsValue_delete(value);
  }
  free(typeSpec);

  return 0;
}