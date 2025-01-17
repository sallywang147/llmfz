#include <stdint.h>
#include <znc/Client.h>
#include <znc/TopicMessage.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);
  CClient client;
  CTopicMessage topic_message;
  client.OnTextMessage(&client, &topic_message);
  return 0;
}