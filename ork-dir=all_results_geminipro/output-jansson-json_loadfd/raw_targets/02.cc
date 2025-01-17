#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

#include "jansson.h"

static int enable_diags;

#define FUZZ_DEBUG(FMT, ...)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           \
  if (enable_diags) {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  \
    fprintf(stderr, FMT, ##__VA_ARGS__);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               \
    fprintf(stderr, "\n");                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             \
  }

#define NUM_COMMAND_BYTES (sizeof(size_t) + 1)

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  json_error_t error;
  size_t flags;

  // Enable or disable diagnostics based on the FUZZ_VERBOSE environment flag.
  enable_diags = (getenv("FUZZ_VERBOSE") != NULL);

  FUZZ_DEBUG("Input data length: %zd", size);

  if (size < NUM_COMMAND_BYTES) {
    return 0;
  }

  // Use the first sizeof(size_t) bytes as load flags.
  flags = *(const size_t *)data;
  data += sizeof(size_t);

  FUZZ_DEBUG("load_flags: 0x%zx\n"
             "& JSON_REJECT_DUPLICATES =  0x%zx\n"
             "& JSON_DECODE_ANY =         0x%zx\n"
             "& JSON_DISABLE_EOF_CHECK =  0x%zx\n"
             "& JSON_DECODE_INT_AS_REAL = 0x%zx\n"
             "& JSON_ALLOW_NUL =          0x%zx\n",
             flags, flags & JSON_REJECT_DUPLICATES, flags & JSON_DECODE_ANY, flags & JSON_DISABLE_EOF_CHECK, flags & JSON_DECODE_INT_AS_REAL, flags & JSON_ALLOW_NUL);

  // Remove the command bytes from the size total.
  size -= NUM_COMMAND_BYTES;

  // Attempt to load the remainder of the data with the given load flags.
  int fd = -1;
  json_t *jobj = json_loadfd(fd, flags, &error);

  if (jobj == NULL) {
    return 0;
  }

  json_decref(jobj);

  return 0;
}