#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "immer/detail/rbts/rrbtree.hpp"

extern "C" {
#include "immer/detail/rbts/concat_center_pos.hpp"
#include "immer/detail/rbts/relaxed_pos.hpp"
#include "immer/detail/rbts/leaf_pos.hpp"
#include "immer/detail/rbts/leaf_sub_pos.hpp"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  auto* concat_center_pos = new immer::detail::rbts::concat_center_pos();
  auto* relaxed_pos = new immer::detail::rbts::relaxed_pos();
  auto* args = new std::__cxx_atomic_base_impl();
  auto* leaf_pos = new immer::detail::rbts::leaf_pos();
  auto* leaf_sub_pos = new immer::detail::rbts::leaf_sub_pos();

  concat_center_pos->concat_center_pos(relaxed_pos, args, args, leaf_pos, args, leaf_sub_pos);

  delete concat_center_pos;
  delete relaxed_pos;
  delete args;
  delete leaf_pos;
  delete leaf_sub_pos;
  return 0;
}