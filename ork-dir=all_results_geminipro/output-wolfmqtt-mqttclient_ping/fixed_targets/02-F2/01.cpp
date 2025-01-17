#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include "MQTTClient.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct _MqttClient client;
  int rc = MqttClient_Init(&client, 1000, 10000, 10000, 10000);
  if (rc != MQTTCLIENT_SUCCESS) {
    return 0;
  }
  rc = MqttClient_Ping(&client);
  MqttClient_Destroy(&client);
  return 0;
}