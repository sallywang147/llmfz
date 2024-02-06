#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

namespace fuzzing {
namespace datasource {

class Datasource {
 public:
  virtual void get(std::vector* this_vector, Datasource* min, size_t max, size_t id,
           size_t) = 0;
  virtual ~Datasource() = default;
};

void get(std::vector* this_vector, Datasource* min, size_t max, size_t id,
           size_t) {
  this_vector->resize(max);
  for (size_t i = 0; i < max; i++) {
    (*this_vector)[i] = static_cast<uint8_t>(id);
  }
}

}  // namespace datasource
}  // namespace fuzzing

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  fuzzing::datasource::Datasource min;
  const size_t max = stream.ConsumeIntegral<size_t>();
  const size_t id = stream.ConsumeIntegral<size_t>();
  std::vector<uint8_t> this_vector;
  fuzzing::datasource::get(&this_vector, &min, max, id, 0);
  return 0;
}