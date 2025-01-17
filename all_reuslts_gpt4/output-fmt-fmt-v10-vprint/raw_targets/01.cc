#include <fuzzer/FuzzedDataProvider.h>
#include <fmt/format.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Consume data for the function parameters
    std::string fmt_str = stream.ConsumeRandomLengthString();
    std::vector<fmt::v10::detail::value> args;

    // Consume remaining data for the arguments
    while (stream.remaining_bytes() > 0) {
        fmt::v10::detail::value arg;
        switch (stream.ConsumeIntegralInRange(0, 2)) {
            case 0: arg = stream.ConsumeIntegral<int>(); break;
            case 1: arg = stream.ConsumeFloatingPoint<double>(); break;
            case 2: arg = stream.ConsumeRandomLengthString(); break;
        }
        args.push_back(arg);
    }

    // Call the function with the fuzzed inputs
    fmt::v10::vprint(stdout, fmt_str.c_str(), args.size(), 0, args.data());

    return 0;
}