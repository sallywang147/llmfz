#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> opt_data = stream.ConsumeRemainingBytes<uint8_t>();
  size_t opt_size = opt_data.size();
  size_t opt_offset = stream.ConsumeIntegralInRange<size_t>(0, opt_size);
  char *opt_ptr = reinterpret_cast<char *>(opt_data.data() + opt_offset);

  size_t opt_len = stream.ConsumeIntegralInRange<size_t>(0, opt_size - opt_offset);
  char *opt_end = opt_ptr + opt_len;

  bool extended_rcode = stream.ConsumeBool();
  std::string rcode_str;
  handleEDNSClientSubnet(&opt_data, opt_size, opt_offset, opt_ptr, opt_end,
                         extended_rcode, &rcode_str);
  return 0;
}