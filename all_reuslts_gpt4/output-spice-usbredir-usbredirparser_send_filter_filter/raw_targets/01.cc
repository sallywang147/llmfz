#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "usbredirparser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  struct usbredirparser* parser = usbredirparser_create();
  if (parser == nullptr) {
    return 0;
  }

  struct usbredirfilter_rule rule;
  rule.interface_class = provider.ConsumeIntegral<uint8_t>();
  rule.interface_subclass = provider.ConsumeIntegral<uint8_t>();
  rule.interface_protocol = provider.ConsumeIntegral<uint8_t>();
  rule.device_class = provider.ConsumeIntegral<uint8_t>();
  rule.device_subclass = provider.ConsumeIntegral<uint8_t>();
  rule.device_protocol = provider.ConsumeIntegral<uint8_t>();
  rule.vendor_id = provider.ConsumeIntegral<uint16_t>();
  rule.product_id = provider.ConsumeIntegral<uint16_t>();
  rule.device_version_bcd = provider.ConsumeIntegral<uint16_t>();

  int count = provider.ConsumeIntegralInRange<int>(0, 10);

  usbredirparser_send_filter_filter(parser, &rule, count);

  usbredirparser_destroy(parser);

  return 0;
}