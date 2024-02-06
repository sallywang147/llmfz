#include <fuzzer/FuzzedDataProvider.h>
#include <vector>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<std::string> thisVector;
  std::exception idException;

  // Consume data to populate the vector
  while (stream.remaining_bytes() > 0) {
    size_t stringLength = stream.ConsumeIntegralInRange<size_t>(0, 100);
    std::string str = stream.ConsumeBytesAsString(stringLength);
    thisVector.push_back(str);
  }

  // Call the function
  fuzzing::datasource::Base::Get<std::vector<std::string>>(&thisVector, &idException, size);

  return 0;
}