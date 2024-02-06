#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>

extern "C" int __XX_main(int argc, char ** argv);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    std::vector<std::string> arguments;
    while (stream.remaining_bytes() > 0) {
        arguments.push_back(stream.ConsumeRandomLengthString());
    }

    // Prepare the argv array
    std::vector<char*> argv;
    for (auto& arg : arguments) {
        argv.push_back(const_cast<char*>(arg.c_str()));
    }
    argv.push_back(nullptr); // argv must be null terminated

    __XX_main(argv.size() - 1, argv.data());

    return 0;
}