#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "test_common.h"

template <class U, class Iter, class... T> void ChooseImplementation(uint8_t byte, std::vector<U> &working, Iter partition_iter, const ::testing::Types<T...> &) {
  static_assert(sizeof...(T) < 256);
  int i = 0;
  constexpr size_t size = sizeof...(T);
  (
      [&]() {
        if (byte % size == i++) {
          T::Sort(working.begin(), partition_iter, working.end());
        }
      }(),
      ...);
}

// Use the first element as a position into the data
extern "C" int LLVMFuzzerTestOneInput(const std::uint8_t *data, std::size_t size) {
  if (size <= 3)
    return 0;
  uint8_t impl = data[0];
  uint16_t partition_point = 0;
  memcpy(&partition_point, data + 1, 2);
  partition_point %= (size - 3);
  std::vector<std::uint8_t> working(data + 3, data + size);
  auto canonical = working;
  const auto partition_iter = working.begin() + partition_point;
  ChooseImplementation(impl, working, partition_iter, miniselect::algorithms::All{});

  bool is_error = false;
  if (partition_iter != working.end()) {
    const auto &nth = *std::min_element(partition_iter, working.end());
    if (!std::all_of(working.begin(), partition_iter, [&](const auto &v) { return v <= nth; })) {
      is_error = true;
    }
    if (!std::all_of(partition_iter, working.end(), [&](const auto &v) { return v >= nth; })) {
      is_error = true;
    }
  }
  if (!std::is_sorted(working.begin(), partition_iter)) {
    is_error = true;
  }
  if (is_error) {
    std::cerr << "FAILED!\nCanonical: ";
    for (const auto &s : canonical) {
      std::cerr << static_cast<int>(s) << ' ';
    }
    std::cerr << std::endl;
    std::cerr << "Got: ";
    for (const auto &s : working) {
      std::cerr << static_cast<int>(s) << ' ';
    }
    std::cerr << std::endl;
    std::cerr << "partition_iter = " << partition_iter - working.begin() << std::endl;
    std::abort();
  }

  return 0;
}
