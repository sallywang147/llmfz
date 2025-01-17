#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "usbredirparser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct usbredirparser *parser = usbredirparser_create();
  if (!parser) {
    return 0;
  }

  struct usbredirfilter_rule rule;
  rule.interface_class = stream.ConsumeIntegral<uint8_t>();
  rule.interface_subclass = stream.ConsumeIntegral<uint8_t>();
  rule.interface_protocol = stream.ConsumeIntegral<uint8_t>();
  rule.device_class = stream.ConsumeIntegral<uint8_t>();
  rule.device_subclass = stream.ConsumeIntegral<uint8_t>();
  rule.device_protocol = stream.ConsumeIntegral<uint8_t>();
  rule.vendor_id = stream.ConsumeIntegral<uint16_t>();
  rule.product_id = stream.ConsumeIntegral<uint16_t>();
  rule.device_version_bcd = stream.ConsumeIntegral<uint16_t>();

  int rule_count = stream.ConsumeIntegralInRange<int>(0, 100);

  usbredirparser_send_filter_filter(parser, &rule, rule_count);

  usbredirparser_destroy(parser);

  return 0;
}