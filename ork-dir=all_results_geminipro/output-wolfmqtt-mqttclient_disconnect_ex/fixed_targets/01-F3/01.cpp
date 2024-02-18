#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include "MQTTClient.h"
#include "MQTTClient_public.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct _MqttClient client;
  struct _MqttDisconnect disconnect;
  int rc = MqttClient_Disconnect_ex(&client, &disconnect);
  return rc;
}