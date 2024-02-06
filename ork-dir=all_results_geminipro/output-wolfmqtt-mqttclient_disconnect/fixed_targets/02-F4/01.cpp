#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include "mqtt_client.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct _MqttClient client;
  MqttClient_Init(&client, stream.ConsumeRemainingBytesAsString().c_str(),
                   stream.ConsumeIntegral<uint16_t>());
  MqttClient_Connect(&client, stream.ConsumeRemainingBytesAsString().c_str(),
                     stream.ConsumeIntegral<uint16_t>(),
                     stream.ConsumeIntegral<uint32_t>());
  MqttClient_Disconnect(&client);
  MqttClient_Destroy(&client);  // Added this line to free the allocated resources.
  return 0;
}