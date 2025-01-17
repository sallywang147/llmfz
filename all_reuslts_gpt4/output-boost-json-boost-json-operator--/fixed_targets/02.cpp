#include <fuzzer/FuzzedDataProvider.h>
#include <boost/json.hpp>
#include <sstream>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    std::string str = stream.ConsumeRemainingBytesAsString();
    
    std::istringstream iss(str);
    boost::json::value jv;
    boost::json::operator>>(&iss, &jv);
    
    return 0;
}