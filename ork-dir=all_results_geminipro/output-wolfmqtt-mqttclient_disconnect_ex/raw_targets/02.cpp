#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "MQTTClient.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct _MqttClient client;
  struct _MqttDisconnect disconnect;
  disconnect.duration = stream.ConsumeIntegral<uint32_t>();
  disconnect.reasonCode = stream.ConsumeIntegral<uint32_t>();
  disconnect.sessionExpiryInterval = stream.ConsumeIntegral<uint32_t>();
  disconnect.serverReference = stream.ConsumeIntegral<uint32_t>();
  disconnect.reasonString = stream.ConsumeRemainingBytesAsString().c_str();
  MqttClient_Disconnect_ex(&client, &disconnect);
  return 0;
}