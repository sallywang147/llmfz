#include <stdint.h>
#include <stddef.h>

#include "ucl.h"
#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Create a parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Create a chunk
    struct ucl_chunk *chunk = (struct ucl_chunk *)malloc(sizeof(struct ucl_chunk));
    if (chunk == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Consume data for the chunk
    chunk->begin = (const unsigned char *)stream.ConsumeRemainingBytesAsString().c_str();
    chunk->len = stream.remaining_bytes();
    chunk->pos = 0;
    chunk->priority = 0;
    chunk->remain = chunk->len;

    // Call the target function
    struct ucl_object_s *obj = ucl_parse_macro_arguments(parser, chunk);

    // Cleanup
    if (obj != NULL) {
        ucl_object_unref(obj);
    }
    free(chunk);
    ucl_parser_free(parser);

    return 0;
}