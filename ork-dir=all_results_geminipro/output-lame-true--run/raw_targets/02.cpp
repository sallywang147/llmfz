#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

struct EncoderCore {
  template <typename T, bool D>
  bool Run(EncoderCore*, char*, size_t, bool) {
    return true;
  }
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  EncoderCore core;
  const size_t input_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  const char* input_buffer = reinterpret_cast<const char*>(stream.ConsumeBytes<char>(input_size).data());
  core.Run<short, true>(nullptr, const_cast<char*>(input_buffer), input_size, false);
  return 0;
}