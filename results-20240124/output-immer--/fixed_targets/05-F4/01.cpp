#include <cstddef>
#include <cstdint>
#include <tuple>
#include <vector>

#include "fuzzer/FuzzedDataProvider.h"
#include "immer/detail/rbts/node.hpp"
#include "immer/detail/rbts/slice_right_mut_visitor.hpp"

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  auto pos = std::make_tuple(
      stream.ConsumeIntegral<uint32_t>(),
      stream.ConsumeIntegral<immer::detail::rbts::node<int,
                                                    immer::memory_policy<
                                                        immer::heap_policy<
                                                            immer::cpp_heap>,
                                                        immer::unsafe_refcount_policy,
                                                        immer::no_lock_policy,
                                                        immer::no_transience_policy,
                                                        false, true>,
                                                    2u, 2u>*>(),
      stream.ConsumeIntegral<uint32_t>(),
      stream.ConsumeIntegral<immer::detail::rbts::node<int,
                                                    immer::memory_policy<
                                                        immer::heap_policy<
                                                            immer::cpp_heap>,
                                                        immer::unsafe_refcount_policy,
                                                        immer::no_lock_policy,
                                                        immer::no_transience_policy,
                                                        false, true>,
                                                    2u, 2u>*>());
  auto last = stream.ConsumeIntegral<immer::detail::rbts::regular_sub_pos*>();
  auto e = stream.ConsumeIntegral<size_t>();
  immer::detail::rbts::slice_right_mut_visitor<
      immer::detail::rbts::node<int,
                                immer::memory_policy<
                                    immer::heap_policy<immer::cpp_heap>,
                                    immer::unsafe_refcount_policy,
                                    immer::no_lock_policy,
                                    immer::no_transience_policy, false, true>,
                              2u, 2u>,
      true, true>::visit_regular<
      immer::detail::rbts::regular_pos<immer::detail::rbts::node<int,
                                                              immer::memory_policy<
                                                                  immer::heap_policy<
                                                                      immer::cpp_heap>,
                                                                  immer::unsafe_refcount_policy,
                                                                  immer::no_lock_policy,
                                                                  immer::no_transience_policy,
                                                                  false, true>,
                                                              2u, 2u>>>(pos, last, e);
  return 0;
}
}