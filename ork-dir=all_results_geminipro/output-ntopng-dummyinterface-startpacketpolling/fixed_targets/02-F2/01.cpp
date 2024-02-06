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

extern "C" {
#include <fuzzer/libfuzzer_macro.h>
}

DEFINE_FUZZER(LLVMFuzzerTestOneInput) {
  FuzzedDataProvider stream(data, size);

  DummyInterface dummy_interface;
  dummy_interface.startPacketPolling(&dummy_interface);
}
```

The fixed code is given above.