#include <fuzzer/FuzzedDataProvider.h>
#include "mqtt_client.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize MqttClient
  MqttClient client;
  MqttClient_Init(&client, NULL, NULL, NULL, NULL, NULL, NULL);

  // Execute the function to fuzz
  MqttClient_Ping(&client);

  return 0;
}