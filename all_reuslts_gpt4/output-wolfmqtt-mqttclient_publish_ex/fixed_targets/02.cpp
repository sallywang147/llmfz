#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mqtt_client.h"

// Define the callback function
void pubCb(int rc) {
    // Do nothing
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the MQTT client
  struct _MqttClient client;
  MqttClient_Init(&client, NULL, NULL, NULL, NULL, NULL, NULL);

  // Create and initialize the MQTT message
  struct _MqttMessage publish;
  MqttMessage_Init(&publish);

  // Consume data for the MQTT message
  size_t topicLen = stream.ConsumeIntegralInRange<size_t>(0, size);
  size_t payloadLen = size - topicLen;

  std::vector<uint8_t> topicData = stream.ConsumeBytes<uint8_t>(topicLen);
  std::vector<uint8_t> payloadData = stream.ConsumeRemainingBytes<uint8_t>();

  // Set the MQTT message fields
  publish.topic_name = reinterpret_cast<char*>(topicData.data());
  publish.topic_name_len = topicLen;
  publish.payload = payloadData.data();
  publish.total_len = payloadLen;

  // Call the target function
  MqttClient_Publish_ex(&client, &publish, &pubCb);

  return 0;
}