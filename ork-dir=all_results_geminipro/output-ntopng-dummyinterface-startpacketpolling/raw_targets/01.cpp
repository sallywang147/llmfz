#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

class DummyInterface {
 public:
  void startPacketPolling(DummyInterface* this_) {
    // Do nothing.
  }
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  DummyInterface dummy_interface;
  dummy_interface.startPacketPolling(&dummy_interface);
  return 0;
}