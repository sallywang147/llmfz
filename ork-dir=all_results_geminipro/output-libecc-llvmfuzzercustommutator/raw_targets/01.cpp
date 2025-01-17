#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" size_t LLVMFuzzerCustomMutator(char* Data, size_t Size,
                                            size_t MaxSize, int Seed) {
  FuzzedDataProvider stream(Data, Size);

  // Check if we should resize the input.
  if (stream.ConsumeBool()) {
    // Resize to a random size between 0 and MaxSize.
    Size = stream.ConsumeIntegralInRange<size_t>(0, MaxSize);
    Data = static_cast<char*>(realloc(Data, Size));
  }

  // Fill the input with random bytes.
  stream.ConsumeBytes<char>(Data, Size);

  // Mutate the input.
  for (size_t i = 0; i < Size; ++i) {
    Data[i] = static_cast<char>(Data[i] ^ stream.ConsumeIntegral<uint8_t>());
  }

  // Return the new size of the input.
  return Size;
}