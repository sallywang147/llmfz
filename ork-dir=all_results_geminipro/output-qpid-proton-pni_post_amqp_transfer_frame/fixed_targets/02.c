#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "proton/engine.h"
#include "proton/transport.h"

extern "C" {
#include "proton/message.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  pn_transport_t* transport = pn_transport();
  pn_transport_bind(transport, pn_localhost());

  const short channel_max = stream.ConsumeIntegral<short>();
  const int window_size = stream.ConsumeIntegral<int>();
  const int max_frame_size = stream.ConsumeIntegral<int>();
  const size_t payload_size = stream.ConsumeIntegralInRange<size_t>(0, 1000);
  const bool expect_transfer = stream.ConsumeBool();
  const bool expect_aborted = stream.ConsumeBool();
  const bool expect_delivery_failed = stream.ConsumeBool();
  const size_t delivery_tag_size = stream.ConsumeIntegralInRange<size_t>(0, 1000);
  const bool has_delivery_tag = stream.ConsumeBool();
  const bool has_properties = stream.ConsumeBool();

  std::vector<uint8_t> payload(payload_size);
  stream.ConsumeBytes<uint8_t>(payload.data(), payload_size);

  pn_bytes_t pn_payload;
  pn_bytes_init(&pn_payload, payload.data(), payload_size);

  std::vector<uint8_t> delivery_tag(delivery_tag_size);
  stream.ConsumeBytes<uint8_t>(delivery_tag.data(), delivery_tag_size);

  pn_data_t* delivery_tag_data = pn_data(delivery_tag.data(), delivery_tag_size);

  std::vector<uint8_t> properties;
  if (has_properties) {
    const size_t properties_size = stream.ConsumeIntegralInRange<size_t>(0, 1000);
    properties.resize(properties_size);
    stream.ConsumeBytes<uint8_t>(properties.data(), properties_size);
  }

  pn_data_t* properties_data = pn_data(properties.data(), properties.size());

  pn_message_t* message = pn_message();
  pn_message_set_body(message, &pn_payload);
  if (has_delivery_tag) {
    pn_message_set_delivery_tag(message, delivery_tag_data);
  }
  if (has_properties) {
    pn_message_set_properties(message, properties_data);
  }

  int ret = pni_post_amqp_transfer_frame(transport, channel_max, window_size,
                                        max_frame_size, message, expect_transfer, expect_aborted,
                                        expect_delivery_failed);
  if (ret != 0) {
    pn_transport_unbind(transport);
    pn_transport_free(transport);
    return 0;
  }

  pn_transport_unbind(transport);
  pn_transport_free(transport);
  return 0;
}