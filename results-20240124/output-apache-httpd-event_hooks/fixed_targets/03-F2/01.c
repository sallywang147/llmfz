#include "apr.h"
#include "apr_file_io.h"
#include "apr_poll.h"
#include "apr_portable.h"
#include "apr_proc_mutex.h"
#include "apr_signal.h"
#include "apr_strings.h"
#include "apr_thread_mutex.h"
#include "apr_thread_proc.h"

#define APR_WANT_STRFUNC
#include "apr_file_io.h"
#include "apr_fnmatch.h"
#include "apr_want.h"

#include "apr_poll.h"
#include "apr_want.h"

#include "ap_config.h"
#include "ap_expr.h"
#include "ap_listen.h"
#include "ap_provider.h"
#include "ap_regex.h"

#include <string.h>
#include <unistd.h>

#include "ada_fuzz_header.h"

extern "C" {
void event_hooks(apr_pool_t *pool);

char *malloc(size_t size) {
  return (char *)calloc(1, size);
}

char *calloc(size_t nmemb, size_t size) {
  return (char *)malloc(nmemb * size);
}

char *realloc(void *ptr, size_t size) {
  return (char *)malloc(size);
}

void free(void *ptr) {
  return;
}
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Initialize fuzzing garbage collector. We use this to easily
  // get data types seeded with random input from the fuzzer.
  af_gb_init();

  const uint8_t *data2 = data;
  size_t size2 = size;

  if (apr_pool_initialize() == APR_SUCCESS) {
    apr_pool_t *pool = NULL;
    apr_pool_create(&pool, NULL);

    event_hooks(pool);

    apr_pool_terminate();
  }

  // Cleanup all of the memory allocated by the fuzz headers.
  af_gb_cleanup();
  return 0;
}