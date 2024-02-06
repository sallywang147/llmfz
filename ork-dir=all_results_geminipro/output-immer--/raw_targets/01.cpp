#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <tuple>

#include "immer/detail/rbts/slice_right_mut_visitor.hpp"
#include "immer/detail/rbts/regular_pos.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Generate a tuple of the form:
  // std::tuple<unsigned int, immer::detail::rbts::node<int, immer::memory_policy<immer::heap_policy<immer::cpp_heap>, immer::unsafe_refcount_policy, immer::no_lock_policy, immer::no_transience_policy, false, true>, 2u, 2u>*, unsigned int, immer::detail::rbts::node<int, immer::memory_policy<immer::heap_policy<immer::cpp_heap>, immer::unsafe_refcount_policy, immer::no_lock_policy, immer::no_transience_policy, false, true>, 2u, 2u>*>
  std::tuple<unsigned int, immer::detail::rbts::node<int, immer::memory_policy<immer::heap_policy<immer::cpp_heap>, immer::unsafe_refcount_policy, immer::no_lock_policy, immer::no_transience_policy, false, true>, 2u, 2u>*, unsigned int, immer::detail::rbts::node<int, immer::memory_policy<immer::heap_policy<immer::cpp_heap>, immer::unsafe_refcount_policy, immer::no_lock_policy, immer::no_transience_policy, false, true>, 2u, 2u>*> tuple;

  std::get<0>(tuple) = provider.ConsumeIntegral<unsigned int>();
  std::get<1>(tuple) = nullptr;
  std::get<2>(tuple) = provider.ConsumeIntegral<unsigned int>();
  std::get<3>(tuple) = nullptr;

  // Generate a regular position.
  immer::detail::rbts::regular_pos<immer::detail::rbts::node<int, immer::memory_policy<immer::heap_policy<immer::cpp_heap>, immer::unsafe_refcount_policy, immer::no_lock_policy, immer::no_transience_policy, false, true>, 2u, 2u>> pos;
  pos.node = nullptr;
  pos.idx = provider.ConsumeIntegral<size_t>();

  // Generate a regular sub position.
  immer::detail::rbts::regular_sub_pos last;
  last.node = nullptr;
  last.idx = provider.ConsumeIntegral<size_t>();

  // Generate an element.
  size_t e = provider.ConsumeIntegral<size_t>();

  // Call the function.
  immer::detail::rbts::slice_right_mut_visitor<immer::detail::rbts::node<int, immer::memory_policy<immer::heap_policy<immer::cpp_heap>, immer::unsafe_refcount_policy, immer::no_lock_policy, immer::no_transience_policy, false, true>, 2u, 2u>, true, true>::visit_regular<immer::detail::rbts::regular_pos<immer::detail::rbts::node<int, immer::memory_policy<immer::heap_policy<immer::cpp_heap>, immer::unsafe_refcount_policy, immer::no_lock_policy, immer::no_transience_policy, false, true>, 2u, 2u> >&>(
      &tuple, &last, e);

  return 0;
}