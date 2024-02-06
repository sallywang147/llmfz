#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string name = stream.ConsumeRemainingBytesAsString();
  struct dpif_3273* class_ptr = nullptr;
  struct dpif_3187* dpifp_ptr = nullptr;
  const bool create = stream.ConsumeBool();

  int result = dpif_netdev_open(class_ptr, const_cast<char*>(name.c_str()), create,
                               &dpifp_ptr);

  if (dpifp_ptr != nullptr) {
    dpif_close(dpifp_ptr);
  }
  return result;
}