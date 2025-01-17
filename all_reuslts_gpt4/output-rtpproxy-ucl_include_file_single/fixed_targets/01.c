#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ucl.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Initialize ucl_parser and ucl_include_params
    struct ucl_parser *parser = ucl_parser_new(0);
    struct ucl_include_params params;
    memset(&params, 0, sizeof(params));

    // Extract data and length from the stream
    size_t len = stream.ConsumeIntegralInRange<size_t>(0, size);
    std::string str = stream.ConsumeBytesAsString(len);
    char *data_str = strdup(str.c_str());

    // Call the target function
    ucl_include_file_single(data_str, len, parser, &params);

    // Cleanup
    ucl_parser_free(parser);
    free(data_str);

    return 0;
}