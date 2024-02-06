#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "MQTTClient.h"

extern "C" {
#include "MQTTClient.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string topic = stream.ConsumeRemainingBytesAsString();
  const std::string payload = stream.ConsumeRemainingBytesAsString();

  MQTTClient client;
  MQTTMessage publish;
  publish.qos = stream.ConsumeIntegralInRange<int>(0, 2);
  publish.retained = stream.ConsumeBool();
  publish.payload = reinterpret_cast<uint8_t*>(const_cast<char*>(payload.c_str()));
  publish.payloadlen = payload.size();
  MQTTClient_deliveryToken token;

  // Fix: Call MqttClient_Publish_ex instead of MQTTClient_PublishMessage
  MqttClient_Publish_ex(&client, topic.c_str(), &publish, NULL);
  return 0;
}
```

The fix is to replace the line:

```c++
  MQTTClient_PublishMessage(&client, topic.c_str(), &publish, &token);
```

with:

```c++
  MqttClient_Publish_ex(&client, topic.c_str(), &publish, NULL);
```

This change calls the correct function, `MqttClient_Publish_ex`, which is expected by the fuzz target.