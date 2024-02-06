#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "usbredirparser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct usbredirparser* parser = usbredirparser_new();
  if (parser == nullptr) {
    return 0;
  }

  const uint32_t num_rules = stream.ConsumeIntegral<uint32_t>();
  for (uint32_t i = 0; i < num_rules; i++) {
    struct usbredirfilter_rule rule;
    memset(&rule, 0, sizeof(rule));

    rule.bus_id = stream.ConsumeIntegral<uint8_t>();
    rule.dev_id = stream.ConsumeIntegral<uint8_t>();
    rule.vendor_id = stream.ConsumeIntegral<uint16_t>();
    rule.product_id = stream.ConsumeIntegral<uint16_t>();
    rule.manufacturer = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 1024));
    rule.product = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 1024));
    rule.serial_number = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 1024));

    usbredirparser_send_filter_rule(parser, &rule, 0); // Fix: Change usbredirparser_send_filter_filter to usbredirparser_send_filter_rule
  }

  usbredirparser_delete(parser);
  return 0;
}