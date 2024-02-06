#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "mqtt_client.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the MQTT client
  struct _MqttClient client;
  MqttClient_Init(&client, NULL, NULL, NULL, NULL, NULL, NULL);

  // Call the function under test
  int result = MqttClient_Disconnect(&client);

  return 0;
}