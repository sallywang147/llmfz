#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <ucl.h>

#include <fuzzer/FuzzedDataProvider.h>

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

  // Initialize the chunk
  chunk->begin = stream.ConsumeBytesAsString(stream.remaining_bytes()).c_str();
  chunk->len = strlen(chunk->begin);
  chunk->pos = 0;
  chunk->priority = 0;

  // Call the function
  struct ucl_object_s *obj = ucl_parse_macro_arguments(parser, chunk);

  // Clean up
  if (obj != NULL) {
    ucl_object_unref(obj);
  }
  free(chunk);
  ucl_parser_free(parser);

  return 0;
}