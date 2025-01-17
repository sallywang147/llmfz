#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "proton/pn_transport.h"

extern "C" {
#include "proton/pn_data.h"
#include "proton/pn_link.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct pn_transport_t transport;
  memset(&transport, 0, sizeof(transport));

  const short channel = stream.ConsumeIntegral<short>();
  const int pri = stream.ConsumeIntegral<int>();
  const int credit = stream.ConsumeIntegral<int>();
  const size_t payload_size = stream.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<uint8_t> payload(payload_size);
  stream.ConsumeBytes<uint8_t>(payload.data(), payload.size());
  const size_t data_size = stream.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<uint8_t> data(data_size);
  stream.ConsumeBytes<uint8_t>(data.data(), data.size());
  const bool settled = stream.ConsumeBool();

  pn_bytes_t payload_bytes = {payload.data(), payload.size()};
  pn_data_t data_bytes = {data.data(), data.size()};
  pni_post_amqp_transfer_frame(&transport, channel, pri, credit,
                               &payload_bytes, false, false, 0, data_size,
                               &data_bytes, settled);

  return 0;
}