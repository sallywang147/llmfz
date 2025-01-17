#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "api/yajl_parse.h"
#include <fuzzer/FuzzedDataProvider.h>

typedef struct {
  int arrayLevel;
  int objectLevel;
} context;

static int yajl_found_null(void *ctx) { return 1; }

static int yajl_found_boolean(void *ctx, int boolean) { return 1; };

static int yajl_found_number(void *ctx, const char *v, unsigned int l) {
  assert(l > 0);
  return 1;
}

static int yajl_found_string(void *ctx, const unsigned char *s, unsigned int l) { return 1; }

static int yajl_found_object_key(void *ctx, const unsigned char *v, unsigned int l) {
  assert(((context *)ctx)->objectLevel > 0);
  return 1;
}

static int yajl_found_start_object(void *ctx) {
  ((context *)ctx)->objectLevel++;
  return 1;
}

static int yajl_found_end_object(void *ctx) {
  assert(((context *)ctx)->objectLevel > 0);
  ((context *)ctx)->objectLevel--;
  return 1;
}

static int yajl_found_start_array(void *ctx) {
  ((context *)ctx)->arrayLevel++;
  return 1;
}

static int yajl_found_end_array(void *ctx) {
  assert(((context *)ctx)->arrayLevel > 0);
  ((context *)ctx)->arrayLevel--;
  return 1;
}

static yajl_callbacks callbacks = {yajl_found_null, yajl_found_boolean, NULL, NULL, yajl_found_number, yajl_found_string, yajl_found_start_object, yajl_found_object_key, yajl_found_end_object, yajl_found_start_array, yajl_found_end_array};

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  context ctx = {
      .arrayLevel = 0,
      .objectLevel = 0,
  };
  yajl_parser_config cfg = {
      .allowComments = stream.ConsumeBool(),
      .checkUTF8 = stream.ConsumeBool(),
  };
  yajl_handle parser = yajl_alloc(&callbacks, &cfg, NULL, (void *)&ctx);

  std::string jsonText = stream.ConsumeRemainingBytesAsString();
  (void)yajl_parse(parser, jsonText.c_str(), jsonText.size());
  
  char *error = yajl_get_error(parser, stream.ConsumeBool(), jsonText.c_str(), jsonText.size());
  if (error) {
    yajl_free_error(parser, error);
  }
  
  yajl_free(parser);

  return 0;
}