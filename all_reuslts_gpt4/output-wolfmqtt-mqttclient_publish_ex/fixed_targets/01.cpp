#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mqtt_client.h"

// Define a callback function for the publish action
void pubCb(int result) {
    // Do nothing, just a placeholder for callback
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize MQTT client
  struct _MqttClient client;
  MqttClient_Init(&client, NULL, NULL, NULL, NULL, NULL, NULL);

  // Initialize MQTT message
  struct _MqttMessage publish;

  // Consume data for the topic and payload of the message
  std::string topic = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, size));
  std::string payload = stream.ConsumeRemainingBytesAsString();

  publish.topic_name = topic.c_str();
  publish.total_len = payload.size();
  publish.buffer = (byte*)payload.c_str();
  publish.buffer_len = payload.size();

  // Call the target function
  MqttClient_Publish_ex(&client, &publish, pubCb);

  return 0;
}