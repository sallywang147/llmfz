#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "MQTTClient.h"

extern "C" {
#include "MQTTClient.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string topic = stream.ConsumeRemainingBytesAsString();
  const std::string payload = stream.ConsumeRemainingBytesAsString();

  MQTTClient client;
  MQTTMessage publish;
  publish.qos = stream.ConsumeIntegralInRange<int>(0, 2);
  publish.retained = stream.ConsumeBool();
  publish.payload = reinterpret_cast<uint8_t*>(const_cast<char*>(payload.c_str()));
  publish.payloadlen = payload.size();
  MQTTClient_deliveryToken token;

  MQTTClient_PublishMessage(&client, topic.c_str(), &publish, &token);
  return 0;
}