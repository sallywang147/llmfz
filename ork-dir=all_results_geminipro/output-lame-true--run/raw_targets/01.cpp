#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

// This is a dummy implementation of the EncoderCore class.
// It is not intended to be used in production code.
class EncoderCore {
 public:
  template <typename T, bool B>
  bool Run(EncoderCore*, char* data, size_t size, bool b) {
    FuzzedDataProvider stream(data, size);
    std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(size);
    void* data_ptr = bytes.data();
    return true;
  }
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  EncoderCore<short, true> encoder;
  encoder.Run(nullptr, const_cast<char*>(reinterpret_cast<const char*>(data)), size,
             false);
  return 0;
}