#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

class DummyInterface {
 public:
  void startPacketPolling(DummyInterface* this_ptr) {
    // Do nothing.
  }
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  DummyInterface dummy_interface;
  dummy_interface.startPacketPolling(&dummy_interface);

  return 0;
}