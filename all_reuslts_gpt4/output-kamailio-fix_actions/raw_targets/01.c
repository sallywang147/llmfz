#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

struct action {
  int type;
  int value;
};

extern int fix_actions(struct action * a);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < sizeof(struct action)) {
    return 0;
  }
  
  FuzzedDataProvider stream(data, size);

  // Extract to user defined object
  struct action act;
  size_t consumed = stream.ConsumeData(&act, sizeof(act));

  if (consumed < sizeof(act)) {
    return 0;
  }

  fix_actions(&act);

  return 0;
}