#include <stdint.h>
extern "C" {
#include <znc/Client.h>
#include <znc/Message.h>
}

void CClient::OnOtherMessage(CSocket *pSocket, CMessage *pMessage) {
  // Do something with the message
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);
  CMessage msg;
  msg.Parse(input);
  CClient client;
  client.OnOtherMessage(NULL, &msg);
  return 0;
}