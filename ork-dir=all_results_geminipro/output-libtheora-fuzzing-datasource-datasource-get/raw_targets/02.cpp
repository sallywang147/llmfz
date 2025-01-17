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
  void get(std::vector* this_vector, Datasource* min, size_t max, size_t id,
           size_t) {
    (void)this_vector;
    (void)min;
    (void)max;
    (void)id;
  }
};

}  // namespace datasource
}  // namespace fuzzing

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  fuzzing::datasource::Datasource min;
  const size_t max = stream.ConsumeIntegral<size_t>();
  const size_t id = stream.ConsumeIntegral<size_t>();
  std::vector<uint8_t> this_vector;
  fuzzing::datasource::Datasource::get(&this_vector, &min, max, id, 0);
  return 0;
}