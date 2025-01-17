#include <stdint.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>
#include "loader.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct VkLayerDispatchTable_ dispatchTable;

  // Initialize the dispatchTable with some dummy values
  dispatchTable.DestroyDevice = nullptr;
  dispatchTable.GetDeviceQueue = nullptr;
  dispatchTable.QueueSubmit = nullptr;

  // Consume some data for the function and layer names
  std::string functionName = stream.ConsumeRandomLengthString();
  std::string layerName = stream.ConsumeRandomLengthString();

  // Call the function under test
  char *result = loader_lookup_device_dispatch_table(&dispatchTable, const_cast<char*>(functionName.c_str()), const_cast<char*>(layerName.c_str()));

  return 0;
}