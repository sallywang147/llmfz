#include <cstdint>
#include <cstddef>
#include <cstring>
#include "fuzzing/datasource/datasource.hpp"

extern "C" {
#include "fuzzing/types/container.hpp"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    fuzzing::datasource::Base ds(data, size);

    try {
        fuzzing::types::Container<unsigned char, false, false> out;
        ds.Get(&out, nullptr, 0);
    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }
    return 0;
}