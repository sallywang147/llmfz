#include <stdint.h>
#include <stddef.h>
#include <ucl.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Extract necessary values
    std::string data_str = stream.ConsumeRandomLengthString();
    bool default_try = stream.ConsumeBool();
    bool default_sign = stream.ConsumeBool();

    // Create necessary objects
    struct ucl_parser *parser = ucl_parser_new(0);
    struct ucl_object_s *args = ucl_object_new();

    // Call the target function
    ucl_include_common(const_cast<char*>(data_str.c_str()), data_str.size(), args, parser, default_try, default_sign);

    // Cleanup
    ucl_object_unref(args);
    ucl_parser_free(parser);

    return 0;
}