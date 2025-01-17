#include <boost/json.hpp>
#include <fuzzer/FuzzedDataProvider.h>
#include <sstream>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Extract a string from the fuzzed data
  std::string str = stream.ConsumeRemainingBytesAsString();
  
  // Create a stringstream from the fuzzed string
  std::istringstream iss(str);
  
  // Create a boost::json::value
  boost::json::value jv;
  
  // Call the function to fuzz
  boost::json::operator>>(&iss, &jv);

  return 0;
}