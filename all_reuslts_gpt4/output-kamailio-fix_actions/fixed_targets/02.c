#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" {
  struct action {
    int type;
    int value;
  };

  int fix_actions(struct action * a);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  while (stream.remaining_bytes() >= sizeof(struct action)) {
    struct action a;
    a.type = stream.ConsumeIntegral<int>();
    a.value = stream.ConsumeIntegral<int>();
    fix_actions(&a);
  }

  return 0;
}