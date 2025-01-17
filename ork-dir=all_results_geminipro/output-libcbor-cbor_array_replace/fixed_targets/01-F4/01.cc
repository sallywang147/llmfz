#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unordered_map>

extern "C" {
#include "cbor.h"
}

static size_t allocated_mem = 0;
static std::unordered_map<void *, size_t> allocated_len_map;
static constexpr size_t kMemoryLimit = 1 << 30;

void *limited_malloc(size_t size) {
  if (size + allocated_mem > kMemoryLimit) {
    return nullptr;
  }
  if (size == 0) {
    return nullptr;
  }
  void *m = malloc(size);
  if (m != nullptr) {
    allocated_mem += size;
    allocated_len_map[m] = size;
  }
  return m;
}

void limited_free(void *ptr) {
  if (ptr != NULL && allocated_len_map.find(ptr) == allocated_len_map.end()) {
    abort();
  }
  free(ptr);
  if (ptr != NULL) {
    allocated_mem -= allocated_len_map[ptr];
    allocated_len_map.erase(ptr);
  }
}

void *limited_realloc(void *ptr, size_t size) {
  if (ptr != NULL && allocated_len_map.find(ptr) == allocated_len_map.end()) {
    abort();
  }
  if (ptr == NULL) {
    return limited_malloc(size);
  }
  long delta = (long)size - allocated_len_map[ptr];
  if (delta + allocated_mem > kMemoryLimit) {
    return nullptr;
  }
  void *new_ptr = realloc(ptr, size);
  if (size > 0 && new_ptr == nullptr) {
    return nullptr;
  }
  allocated_mem += delta;
  allocated_len_map.erase(ptr);
  if (size > 0) {
    allocated_len_map[new_ptr] = size;
  }
  return new_ptr;
}

struct State {
  FILE *fout;

  State() : fout(fopen("/dev/null", "r")) { cbor_set_allocs(limited_malloc, limited_realloc, limited_free); }
};

static State kState;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  cbor_load_result result;
  cbor_item_t *item = cbor_load(Data, Size, &result);
  if (result.error.code == CBOR_ERR_NONE) {
    cbor_describe(item, kState.fout);
    unsigned char *buffer;
    size_t buffer_size;
    cbor_serialize_alloc(item, &buffer, &buffer_size);
    cbor_free(buffer); // Fix: Use cbor_free instead of free

    FuzzedDataProvider provider(Data, Size);
    size_t index = provider.ConsumeIntegralInRange<size_t>(0, cbor_array_size(item));
    cbor_item_t *value = cbor_load(provider.ConsumeRemainingBytes(), provider.remaining_bytes(), &result);
    if (result.error.code == CBOR_ERR_NONE) {
      cbor_array_replace(item, index, value);
      cbor_decref(&value);
    }
    cbor_decref(&item);
  }
  return 0;
}