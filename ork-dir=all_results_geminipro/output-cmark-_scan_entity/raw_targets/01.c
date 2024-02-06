#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t input_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* input = new char[input_size + 1];
  stream.ConsumeBytes<char>(input, input_size);
  input[input_size] = '\0';

  int result = _scan_entity(input);

  delete[] input;
  return result;
}