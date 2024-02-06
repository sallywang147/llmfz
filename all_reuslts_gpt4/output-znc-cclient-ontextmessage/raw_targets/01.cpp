#include <fuzzer/FuzzedDataProvider.h>
#include <stdint.h>
#include <znc/Client.h>
#include <znc/TopicMessage.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  CClient client;
  CTopicMessage topicMessage;

  client.OnTextMessage(&client, &topicMessage);

  return 0;
}