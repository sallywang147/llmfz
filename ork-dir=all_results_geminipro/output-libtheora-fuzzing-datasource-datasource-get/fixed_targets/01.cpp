#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

namespace fuzzing {
namespace datasource {

class Datasource {
 public:
  void get(std::vector<uint8_t>& this_vec, Datasource* min, size_t max, size_t id,
           size_t) {
    this_vec.clear();
    this_vec.reserve(max);
    for (size_t i = 0; i < max; i++) {
      this_vec.push_back(static_cast<uint8_t>(id));
    }
  }
};

}  // namespace datasource
}  // namespace fuzzing

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  size_t max_size = stream.ConsumeIntegralInRange<size_t>(1, 10000);
  size_t id = stream.ConsumeIntegralInRange<size_t>(0, 10000);
  std::vector<uint8_t> vec;
  fuzzing::datasource::Datasource src;
  src.get(vec, nullptr, max_size, id, 0);
  return 0;
}
}