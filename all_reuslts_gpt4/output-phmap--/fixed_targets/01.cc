#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "parallel_hashmap/phmap.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Define the allocator type
    using AllocType = std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > > >;

    // Create a HashtablezInfoHandle
    phmap::priv::HashtablezInfoHandle* handle = new phmap::priv::HashtablezInfoHandle();

    // Consume some data for the char* and size_t parameters
    std::string str = stream.ConsumeBytesAsString(stream.remaining_bytes());
    char* p = const_cast<char*>(str.c_str());
    size_t n = str.size();

    // Call the function under test
    phmap::priv::Deallocate<8ul, AllocType>(handle, p, n);

    // Cleanup
    delete handle;

    return 0;
}