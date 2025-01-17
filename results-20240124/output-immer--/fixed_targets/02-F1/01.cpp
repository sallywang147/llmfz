#include <cstddef>
#include <cstdint>
#include <tuple>

#include "fuzzer/FuzzedDataProvider.h"
#include "immer/detail/rbts/rbts.hpp"
#include "immer/detail/rbts/slice_right_mut_visitor.hpp"
#include "immer/detail/rbts/visitor.hpp"
#include "immer/memory_policy.hpp"
#include "immer/refcount/unsafe_refcount_policy.hpp"

using namespace std;
using namespace immer;
using namespace immer::detail;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  auto node = rbts::make_node<int, memory_policy<heap_policy<cpp_heap>,
                                                  unsafe_refcount_policy,
                                                  no_lock_policy,
                                                  no_transience_policy,
                                                  false,
                                                  true>>(2, 2);
  auto pos = tuple<unsigned int, rbts::node<int, memory_policy<heap_policy<cpp_heap>,
                                                                unsafe_refcount_policy,
                                                                no_lock_policy,
                                                                no_transience_policy,
                                                                false,
                                                                true>,
                                            2u,
                                            2u>*,
                   unsigned int,
                   rbts::node<int, memory_policy<heap_policy<cpp_heap>,
                                                 unsafe_refcount_policy,
                                                 no_lock_policy,
                                                 no_transience_policy,
                                                 false,
                                                 true>,
                                            2u,
                                            2u>*>(
      0, &node, 0, &node);
  auto last = rbts::regular_sub_pos{};
  auto e = provider.ConsumeIntegral<size_t>();

  rbts::slice_right_mut_visitor<rbts::node<int, memory_policy<heap_policy<cpp_heap>,
                                                               unsafe_refcount_policy,
                                                               no_lock_policy,
                                                               no_transience_policy,
                                                               false,
                                                               true>,
                                            2u,
                                            2u>,
                                true,
                                true>::visit_regular<rbts::regular_pos<rbts::node<int,
                                                                               memory_policy<heap_policy<cpp_heap>,
                                                                                             unsafe_refcount_policy,
                                                                                             no_lock_policy,
                                                                                             no_transience_policy,
                                                                                             false,
                                                                                             true>,
                                                                               2u,
                                                                               2u>>>(
      &pos, &last, e);

  return 0;
}