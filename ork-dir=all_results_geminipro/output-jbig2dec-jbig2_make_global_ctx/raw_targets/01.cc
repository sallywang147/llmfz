#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jbig2.h"

#define ALIGNMENT ((size_t)16)
#define KBYTE ((size_t)1024)
#define MBYTE (1024 * KBYTE)
#define GBYTE (1024 * MBYTE)
#define MAX_ALLOCATION (32 * MBYTE)

static size_t used;

static void *jbig2_fuzzer_reached_limit(size_t oldsize, size_t size) {
  if (oldsize == 0)
    fprintf(stderr, "limit: %zu Mbyte used: %zu Mbyte allocation: %zu: limit reached\n", MAX_ALLOCATION / MBYTE, used / MBYTE, size);
  else
    fprintf(stderr, "limit: %zu Mbyte used: %zu Mbyte reallocation: %zu -> %zu: limit reached\n", MAX_ALLOCATION / MBYTE, used / MBYTE, oldsize, size);
  fflush(0);
  return NULL;
}

static void *jbig2_fuzzer_alloc(Jbig2Allocator *allocator, size_t size) {
  char *ptr = NULL;

  if (size == 0)
    return NULL;
  if (size > SIZE_MAX - ALIGNMENT)
    return NULL;
  if (size + ALIGNMENT > MAX_ALLOCATION - used)
    return jbig2_fuzzer_reached_limit(0, size + ALIGNMENT);

  ptr = (char *)malloc(size + ALIGNMENT);
  if (ptr == NULL)
    return NULL;

  memcpy(ptr, &size, sizeof(size));
  used += size + ALIGNMENT;

  return ptr + ALIGNMENT;
}

static void jbig2_fuzzer_free(Jbig2Allocator *allocator, void *ptr) {
  size_t size;

  if (ptr == NULL)
    return;
  if (ptr < (void *)ALIGNMENT)
    return;

  ptr = (char *)ptr - ALIGNMENT;
  memcpy(&size, ptr, sizeof(size));

  used -= size + ALIGNMENT;
  free(ptr);
}

static void *jbig2_fuzzer_realloc(Jbig2Allocator *allocator, void *old, size_t size) {
  size_t oldsize;
  char *ptr;

  if (old == NULL)
    return jbig2_fuzzer_alloc(allocator, size);
  if (old < (void *)ALIGNMENT)
    return NULL;

  if (size == 0) {
    jbig2_fuzzer_free(allocator, old);
    return NULL;
  }
  if (size > SIZE_MAX - ALIGNMENT)
    return NULL;

  old = (char *)old - ALIGNMENT;
  memcpy(&oldsize, old, sizeof(oldsize));

  if (size + ALIGNMENT > MAX_ALLOCATION - used + oldsize + ALIGNMENT)
    return jbig2_fuzzer_reached_limit(oldsize + ALIGNMENT, size + ALIGNMENT);

  ptr = (char *)realloc(old, size + ALIGNMENT);
  if (ptr == NULL)
    return NULL;

  used -= oldsize + ALIGNMENT;
  memcpy(ptr, &size, sizeof(size));
  used += size + ALIGNMENT;

  return ptr + ALIGNMENT;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  Jbig2Allocator allocator;
  Jbig2Ctx *ctx = NULL;
  Jbig2GlobalCtx *global_ctx = NULL;

  used = 0;

  allocator.alloc = jbig2_fuzzer_alloc;
  allocator.free = jbig2_fuzzer_free;
  allocator.realloc = jbig2_fuzzer_realloc;

  ctx = jbig2_ctx_new(&allocator, (Jbig2Options)0, NULL, NULL, NULL);
  if (ctx == NULL)
    return 0;

  global_ctx = jbig2_make_global_ctx(ctx);
  if (global_ctx == NULL) {
    jbig2_ctx_free(ctx);
    return 0;
  }

  jbig2_global_ctx_free(global_ctx);
  jbig2_ctx_free(ctx);

  return 0;
}