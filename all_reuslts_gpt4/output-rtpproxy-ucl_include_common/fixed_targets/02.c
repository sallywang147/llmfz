#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ucl.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Extract integral values
    size_t len = stream.ConsumeIntegral<size_t>();
    bool default_try = stream.ConsumeBool();
    bool default_sign = stream.ConsumeBool();

    // Extract a string. You MUST use .c_str() to use result as pointer
    std::string str = stream.ConsumeRemainingBytesAsString();
    char *data_ptr = strdup(str.c_str());

    // Initialize parser and args
    struct ucl_parser *parser = ucl_parser_new(0);
    struct ucl_object_s *args = ucl_object_typed_new(UCL_OBJECT);

    // Call the function
    ucl_include_common(data_ptr, len, args, parser, default_try, default_sign);

    // Cleanup
    ucl_parser_free(parser);
    ucl_object_unref(args);
    free(data_ptr);

    return 0;
}