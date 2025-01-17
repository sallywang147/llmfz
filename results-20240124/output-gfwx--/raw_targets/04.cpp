 #include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <vector>

namespace fuzzing {
namespace types {

template <typename T, bool IsSigned, bool IsConst>
class Container {
  public:
    Container(std::vector<T> data) : data_(std::move(data)) { }
    const std::vector<T>& data() const { return data_; }

  private:
    std::vector<T> data_;
};

}  // namespace types
}  // namespace fuzzing

namespace fuzzing {
namespace datasource {

class Base {
  public:
    template <typename T>
    void Get(T* this, std::exception* id, size_t) {
      FuzzedDataProvider stream(id->what(), std::strlen(id->what()));
      const size_t size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
      std::vector<uint8_t> data = stream.ConsumeBytes<uint8_t>(size);
      *this = types::Container<uint8_t, false, false>(std::move(data));
    }
};

}  // namespace datasource
}  // namespace fuzzing

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  fuzzing::datasource::Base base;
  fuzzing::types::Container<uint8_t, false, false> container;
  base.Get(&container, new std::exception("test"), 0);
  return 0;
}