#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "mqtt_client.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the MQTT client
  MqttClient client;
  MqttClient_Init(&client, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0);

  // Call the function under test
  MqttClient_Ping(&client);

  return 0;
}