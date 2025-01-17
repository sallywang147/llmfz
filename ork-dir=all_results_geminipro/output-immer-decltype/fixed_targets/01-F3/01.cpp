#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include <immer/detail/rbts/concat_center_pos.hpp>
#include <immer/detail/rbts/relaxed_pos.hpp>
#include <immer/detail/rbts/leaf_pos.hpp>
#include <immer/detail/rbts/leaf_sub_pos.hpp>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct immer::detail::rbts::concat_center_pos* this_ptr =
      new struct immer::detail::rbts::concat_center_pos();
  struct immer::detail::rbts::relaxed_pos* v_ptr =
      new struct immer::detail::rbts::relaxed_pos();
  struct std::__cxx_atomic_base_impl* args_ptr =
      new struct std::__cxx_atomic_base_impl();
  struct immer::detail::rbts::leaf_pos* args_ptr2 =
      new struct immer::detail::rbts::leaf_pos();
  struct std::__cxx_atomic_base_impl* args_ptr3 =
      new struct std::__cxx_atomic_base_impl();
  struct immer::detail::rbts::leaf_sub_pos* args_ptr4 =
      new struct immer::detail::rbts::leaf_sub_pos();

  // Call the target function
  immer::detail::rbts::concat_center_pos::concat_center_pos(
      this_ptr, v_ptr, args_ptr, args_ptr, args_ptr2, args_ptr3, args_ptr4);

  immer::detail::rbts::concat_center_pos::concat_center_pos(
      this_ptr, v_ptr, args_ptr, args_ptr, args_ptr2, args_ptr3, args_ptr4);

  delete this_ptr;
  delete v_ptr;
  delete args_ptr;
  delete args_ptr2;
  delete args_ptr3;
  delete args_ptr4;
  return 0;
}