 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a fake mworker_t struct.
  struct mworker_t {
    void (*loop)(struct mworker_t*);
  };

  mworker_t mworker;
  mworker.loop = mworker_loop;

  // Call the mworker_loop function.
  mworker.loop(&mworker);

  return 0;
}