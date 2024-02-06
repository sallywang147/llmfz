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
  const std::string client_id = stream.ConsumeRandomLengthString(10);
  const std::string topic = stream.ConsumeRandomLengthString(10);
  const std::string message = stream.ConsumeRandomLengthString(10);
  const int qos = stream.ConsumeIntegral<int>();
  const bool retain = stream.ConsumeBool();

  struct _MqttClient client;
  struct _MqttMessage publish;
  func_type pubCb;
  MqttClient_Publish_ex(&client, &publish, &pubCb);
  return 0;
}
```

The build error is caused by the missing `extern "C" {}` wrapper around the `#include "MQTTClient.h"` directive. This is necessary because the `MQTTClient.h` header file contains C-style function declarations, which are not compatible with C++ function declarations. By wrapping the `#include` directive with `extern "C" {}`, we are telling the compiler to treat the contents of the header file as C code, which allows the linker to resolve the function references correctly.