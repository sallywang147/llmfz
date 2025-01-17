#include <fuzzer/FuzzedDataProvider.h>

#include <vector>

namespace fuzzing {
namespace datasource {
class Base {
 public:
  template <typename T>
  void Get(T* this_, std::exception* id, size_t) {
    FuzzedDataProvider stream(id->what(), strlen(id->what()));
    *this_ = stream.ConsumeRemainingBytes<T>();
  }
};
}  // namespace datasource
}  // namespace fuzzing

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  std::exception exception;
  fuzzing::datasource::Base base;
  std::vector<std::string> strings;
  base.Get<std::vector<std::string>>(&strings, &exception, size);
  return 0;
}