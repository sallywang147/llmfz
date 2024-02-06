#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <dns/dns.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct dns_view* view = dns_view_create();
  if (view == nullptr) {
    return 0;
  }

  const bool newonly = stream.ConsumeBool();
  const std::vector<uint8_t> arg_bytes = stream.ConsumeRemainingBytes();
  char* arg = reinterpret_cast<char*>(arg_bytes.data());

  int ret = dns_view_asyncload(view, newonly, nullptr, arg);
  if (ret == 0) {
    dns_view_delete(view);
  }

  return 0;
}