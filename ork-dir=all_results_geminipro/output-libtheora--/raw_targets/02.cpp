#include <fuzzer/FuzzedDataProvider.h>

#include <string>
#include <vector>

namespace fuzzing {
namespace datasource {

class Base {
 public:
  template <class T>
  void Get(T* this_, std::exception* id, size_t) {
    FuzzedDataProvider stream(data, size);
    std::vector<std::string> result;
    while (stream.remaining_bytes() > 0) {
      result.push_back(stream.ConsumeRemainingBytesAsString());
    }
    *this_ = result;
  }
};

}  // namespace datasource
}  // namespace fuzzing

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  std::vector<std::string> result;
  fuzzing::datasource::Base base;
  base.Get(&result, nullptr, 0);
  return 0;
}