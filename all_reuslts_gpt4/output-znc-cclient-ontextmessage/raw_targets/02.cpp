#include <fuzzer/FuzzedDataProvider.h>
#include <stdint.h>
#include <znc/Client.h>
#include <znc/Message.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create a CClient object
  CClient client;

  // Create a CTopicMessage object
  std::string topic = stream.ConsumeRandomLengthString();
  CTopicMessage topicMessage(topic);

  // Call the function to fuzz
  client.OnTextMessage(&client, &topicMessage);

  return 0;
}