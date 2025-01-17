#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "usbredirparser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct usbredirparser* parser = usbredirparser_new();
  if (parser == nullptr) {
    return 0;
  }

  const size_t num_rules = stream.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<struct usbredirfilter_rule> rules(num_rules);
  for (size_t i = 0; i < num_rules; i++) {
    rules[i].vendor_id = stream.ConsumeIntegral<uint16_t>();
    rules[i].product_id = stream.ConsumeIntegral<uint16_t>();
    rules[i].class_id = stream.ConsumeIntegral<uint16_t>();
    rules[i].subclass_id = stream.ConsumeIntegral<uint16_t>();
    rules[i].protocol_id = stream.ConsumeIntegral<uint16_t>();
    rules[i].flags = stream.ConsumeIntegral<uint16_t>();
    rules[i].bus_id = stream.ConsumeIntegral<uint8_t>();
    rules[i].port_id = stream.ConsumeIntegral<uint8_t>();
    rules[i].device_address = stream.ConsumeIntegral<uint8_t>();
    rules[i].function_number = stream.ConsumeIntegral<uint8_t>();
    rules[i].interface_number = stream.ConsumeIntegral<uint8_t>();
    rules[i].alternate_setting = stream.ConsumeIntegral<uint8_t>();
  }

  usbredirparser_send_filter_filter(parser, rules.data(), num_rules);
  usbredirparser_free(parser);
  return 0;
}