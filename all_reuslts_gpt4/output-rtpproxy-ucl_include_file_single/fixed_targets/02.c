#include <stdint.h>
#include <stddef.h>
#include <ucl.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Create and initialize ucl_parser and ucl_include_params
    struct ucl_parser *parser = ucl_parser_new(0);
    struct ucl_include_params params = {0};

    // Extract a string from the data stream
    std::string str = stream.ConsumeRandomLengthString();
    char *cstr = const_cast<char*>(str.c_str());

    // Call the target function
    ucl_include_file_single(cstr, str.size(), parser, &params);

    // Free the parser
    ucl_parser_free(parser);

    return 0;
}