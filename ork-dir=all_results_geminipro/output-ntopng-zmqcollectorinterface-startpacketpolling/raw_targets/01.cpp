#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "ZMQCollectorInterface.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  ZMQCollectorInterface* obj = new ZMQCollectorInterface();
  obj->startPacketPolling(obj);
  delete obj;
  return 0;
}