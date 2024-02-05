#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // We'll need at least 5 bytes to proceed. 4 for the int and 1 for the size_t.
  if (size < 5) {
    return 0;
  }

  // Consume 4 bytes for the int.
  int val = stream.ConsumeIntegral<int>();

  // Consume the remaining bytes as a vector of size_t.
  std::vector<size_t> name = stream.ConsumeRemainingBytes<size_t>();

  // Call the function under test.
  register_int_index(name.data(), name.size(), val);

  return 0;
}