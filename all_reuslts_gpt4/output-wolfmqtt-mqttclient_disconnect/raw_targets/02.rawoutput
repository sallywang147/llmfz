#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include "mqtt_client.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    
    // Create an instance of _MqttClient
    _MqttClient client;

    // Consume data to initialize the _MqttClient struct
    client.cmd_timeout_ms = stream.ConsumeIntegral<int>();
    client.keep_alive_sec = stream.ConsumeIntegral<int>();
    client.clean_session = stream.ConsumeBool();
    client.enable_lwt = stream.ConsumeBool();
    client.use_tls = stream.ConsumeBool();
    
    // Consume remaining data to initialize the client_id
    std::string client_id = stream.ConsumeRemainingBytesAsString();
    client.client_id = client_id.c_str();
    
    // Call the function to be fuzzed
    MqttClient_Disconnect(&client);

    return 0;
}