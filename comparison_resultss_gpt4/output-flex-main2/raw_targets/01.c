#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    int argc = stream.ConsumeIntegralInRange<int>(1, 10);
    std::vector<std::string> arguments(argc);
    std::vector<char*> argv(argc);

    for (int i = 0; i < argc; ++i) {
        arguments[i] = stream.ConsumeRandomLengthString();
        argv[i] = const_cast<char*>(arguments[i].c_str());
    }

    argv.push_back(nullptr);  // argv must be null-terminated

    main2(argc, argv.data());

    return 0;
}