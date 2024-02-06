#include <fuzzer/FuzzedDataProvider.h>
#include <blake2.h>

extern "C" {
#include <blake2.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t output_length = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  const size_t input_length = stream.ConsumeIntegralInRange<size_t>(0, 1024);

  char* output = new char[output_length];
  char* input = new char[input_length];

  stream.ConsumeBytes(input, input_length);

  blake2b_long(output, output_length, input, input_length);

  delete[] output;
  delete[] input;

  return 0;
}