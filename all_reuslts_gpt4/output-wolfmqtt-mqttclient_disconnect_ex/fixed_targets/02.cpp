#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mqtt_client.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize MQTT client
  struct _MqttClient client;
  MqttClient_Init(&client, NULL, NULL, NULL, NULL, NULL, NULL);

  // Initialize MQTT disconnect
  struct _MqttDisconnect disconnect;
  MqttDisconnect_Init(&disconnect);

  // Call the function to fuzz
  MqttClient_Disconnect_ex(&client, &disconnect);

  return 0;
}