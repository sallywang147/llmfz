 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <tuple>

#include "immer/detail/rbts/node.hpp"
#include "immer/detail/rbts/slice_right_mut_visitor.hpp"
#include "immer/detail/rbts/regular_pos.hpp"
#include "immer/detail/rbts/regular_sub_pos.hpp"

using namespace immer;
using namespace immer::detail;
using namespace immer::detail::rbts;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  node<int, memory_policy<heap_policy<cpp_heap>,
                           unsafe_refcount_policy,
                           no_lock_policy,
                           no_transience_policy,
                           false,
                           true>,
       2u,
       2u>* node_ptr = nullptr;
  node<int, memory_policy<heap_policy<cpp_heap>,
                           unsafe_refcount_policy,
                           no_lock_policy,
                           no_transience_policy,
                           false,
                           true>,
       2u,
       2u>* node_ptr2 = nullptr;
  slice_right_mut_visitor<node<int, memory_policy<heap_policy<cpp_heap>,
                                                    unsafe_refcount_policy,
                                                    no_lock_policy,
                                                    no_transience_policy,
                                                    false,
                                                    true>,
                                 2u,
                                 2u>,
                         true,
                         true> visitor;

  std::tuple<unsigned int, node<int, memory_policy<heap_policy<cpp_heap>,
                                                    unsafe_refcount_policy,
                                                    no_lock_policy,
                                                    no_transience_policy,
                                                    false,
                                                    true>,
                                 2u,
                                 2u>*,
             unsigned int,
             node<int, memory_policy<heap_policy<cpp_heap>,
                                                    unsafe_refcount_policy,
                                                    no_lock_policy,
                                                    no_transience_policy,
                                                    false,
                                                    true>,
                                 2u,
                                 2u>*> pos;
  regular_sub_pos last;
  size_t e = stream.ConsumeIntegral<size_t>();
  void std::__1::tuple<unsigned int, immer::detail::rbts::node<int, immer::memory_policy<immer::heap_policy<immer::cpp_heap>, immer::unsafe_refcount_policy, immer::no_lock_policy, immer::no_transience_policy, false, true>, 2u, 2u>*, unsigned int, immer::detail::rbts::node<int, immer::memory_policy<immer::heap_policy<immer::cpp_heap>, immer::unsafe_refcount_policy, immer::no_lock_policy, immer::no_transience_policy, false, true>, 2u, 2u>*> immer::detail::rbts::slice_right_mut_visitor<immer::detail::rbts::node<int, immer::memory_policy<immer::heap_policy<immer::cpp_heap>, immer::unsafe_refcount_policy, immer::no_lock_policy, immer::no_transience_policy, false, true>, 2u, 2u>, true, true>::visit_regular<immer::detail::rbts::regular_pos<immer::detail::rbts::node<int, immer::memory_policy<immer::heap_policy<immer::cpp_heap>, immer::unsafe_refcount_policy, immer::no_lock_policy, immer::no_transience_policy, false, true>, 2u, 2u> >&>(std::tuple * pos, struct immer::detail::rbts::regular_sub_pos * last, size_t e)(&pos, &last, e);
  return 0;
}