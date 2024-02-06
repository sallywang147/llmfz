#include "../common/platform.h"
#include "../dec/internal_state.h"
#include <brunsli/brunsli_decode.h>
#include <brunsli/status.h>
#include <brunsli/types.h>

extern "C" {
#include <brunsli/decode.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  brunsli::internal::dec::InternalState* state = new brunsli::internal::dec::InternalState();
  brunsli::BrunsliStatus status = brunsli::BrunsliDecode(data, size, state);
  if (status == brunsli::BRUNSLI_OK) {
    delete state;
  }
  return 0;
}

extern "C" void brunsli::internal::dec::InternalState::~InternalState() {
  // Fix the destructor to delete the allocated memory.
  delete[] this->block_type_;
  delete[] this->block_len_;
  delete[] this->block_huff_;
  delete[] this->block_huff_code_;
  delete[] this->block_huff_offset_;
  delete[] this->block_huff_symbol_;
  delete[] this->block_huff_data_;
  delete[] this->block_huff_data_size_;
  delete[] this->block_meta_data_;
  delete[] this->block_meta_data_size_;
  delete[] this->block_type_code_;
  delete[] this->block_type_offset_;
  delete[] this->block_type_symbol_;
  delete[] this->block_type_data_;
  delete[] this->block_type_data_size_;
  delete[] this->block_type_data_offset_;
  delete[] this->block_type_data_size_offset_;
  delete[] this->block_type_data_offset_offset_;
  delete[] this->block_type_data_size_size_offset_;
  delete[] this->block_type_data_offset_size_offset_;
  delete[] this->block_type_data_size_size_size_offset_;
  delete[] this->block_type_data_offset_size_size_offset_;
  delete[] this->block_type_data_size_size_size_size_offset_;
  delete[] this->block_type_data_offset_size_size_size_offset_;
  delete[] this->block_type_data_size_size_size_size_size_offset_;
  delete[] this->block_type_data_offset_size_size_size_size_offset_;
  delete[] this->block_type_data_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_offset_size_size_size_size_size_offset_;
  delete[] this->block_type_data_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_offset_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_offset_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_offset_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_offset_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_size_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_offset_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_size_size_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_offset_size_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_size_size_size_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_offset_size_size_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_size_size_size_size_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_offset_size_size_size_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_offset_size_size_size_size_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_offset_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_offset_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_offset_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_offset_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_offset_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_offset_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_offset_;
  delete[] this->block_type_data_offset_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size_size