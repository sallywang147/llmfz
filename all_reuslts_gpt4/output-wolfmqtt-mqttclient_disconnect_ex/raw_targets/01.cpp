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
  MqttClient client;
  MqttNet net;
  int ret = MqttClient_Init(&client, &net, NULL, NULL, 1000, NULL, 0);
  if (ret != MQTT_CODE_SUCCESS) {
    return 0;
  }

  // Initialize MQTT disconnect
  MqttDisconnect disconnect;
  MqttDisconnect_Init(&disconnect);

  // Fuzz the disconnect reason code
  disconnect.reasonCode = stream.ConsumeIntegral<uint8_t>();

  // Fuzz the disconnect properties
  disconnect.props.packetId = stream.ConsumeIntegral<uint16_t>();
  disconnect.props.reasonString = stream.ConsumeRandomLengthString().c_str();

  // Call the function to fuzz
  MqttClient_Disconnect_ex(&client, &disconnect);

  return 0;
}