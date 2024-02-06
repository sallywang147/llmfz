#include <string>
#include <vector>

#include "Poco/RegularExpression.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);
  Poco::RegularExpression re(".*");
  std::string replacement("replacement");
  size_t count = re.substOne(&input, 0, &replacement, 0);
  return 0;
}