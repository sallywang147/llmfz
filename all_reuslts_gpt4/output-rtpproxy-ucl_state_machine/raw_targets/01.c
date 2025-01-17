#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ucl.h"

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    struct ucl_parser *parser = ucl_parser_new(0);

    if (parser == NULL) {
        return 0;
    }

    std::string str = stream.ConsumeRemainingBytesAsString();
    const char *c_str = str.c_str();

    ucl_parser_add_chunk(parser, (const unsigned char *)c_str, str.size());

    ucl_state_machine(parser);

    ucl_parser_free(parser);

    return 0;
}