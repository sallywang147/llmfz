#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "MQTTClient.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const std::string client_id = stream.ConsumeRemainingBytesAsString();
  MQTTClient client = MQTTClient(client_id.c_str());

  int ret = MqttClient_Ping(&client);
  if (ret != MQTTCLIENT_SUCCESS) {
    return 0;
  }

  return 0;
}