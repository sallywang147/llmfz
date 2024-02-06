#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "immer/detail/rbts/concat_center_pos.hpp"
#include "immer/detail/rbts/relaxed_pos.hpp"
#include "immer/detail/rbts/leaf_pos.hpp"
#include "immer/detail/rbts/leaf_sub_pos.hpp"

struct __cxx_atomic_base_impl {
    int value;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    immer::detail::rbts::concat_center_pos concat_center_pos_obj;
    immer::detail::rbts::relaxed_pos relaxed_pos_obj;
    immer::detail::rbts::leaf_pos leaf_pos_obj;
    immer::detail::rbts::leaf_sub_pos leaf_sub_pos_obj;

    std::__cxx_atomic_base_impl args1;
    std::__cxx_atomic_base_impl args2;
    std::__cxx_atomic_base_impl args3;
    std::__cxx_atomic_base_impl args4;

    // Initialize the objects
    concat_center_pos_obj = stream.ConsumeIntegral<immer::detail::rbts::concat_center_pos>();
    relaxed_pos_obj = stream.ConsumeIntegral<immer::detail::rbts::relaxed_pos>();
    leaf_pos_obj = stream.ConsumeIntegral<immer::detail::rbts::leaf_pos>();
    leaf_sub_pos_obj = stream.ConsumeIntegral<immer::detail::rbts::leaf_sub_pos>();

    args1.value = stream.ConsumeIntegral<int>();
    args2.value = stream.ConsumeIntegral<int>();
    args3.value = stream.ConsumeIntegral<int>();
    args4.value = stream.ConsumeIntegral<int>();

    decltype(&concat_center_pos_obj, &relaxed_pos_obj, &args1, &args2, &leaf_pos_obj, &args3, &leaf_sub_pos_obj);

    return 0;
}