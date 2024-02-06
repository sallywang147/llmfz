#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

struct EncoderCore {
  bool Run(short* data, size_t size, bool) {
    return true;
  }
};

extern "C" {
#include <stddef.h>
#include <stdint.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  EncoderCore core;
  const size_t input_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  char* input_buffer = const_cast<char*>(stream.ConsumeBytes<char>(input_size).data());
  core.Run(reinterpret_cast<short*>(input_buffer), input_size, false);
  return 0;
}