#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "mqtt_client.h"

extern "C" {
#include "mqtt_client.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct _MqttClient client;
  MqttClient_Init(&client, 0, 0, 0, 0, 0, 0, 0);
  MqttClient_Connect(&client, "localhost", 1883, 1000);
  MqttClient_Disconnect(&client);
  return 0;
}