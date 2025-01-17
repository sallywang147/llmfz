#include <stdint.h>
#include <znc/Client.h>
#include <znc/IRCSock.h>
#include <znc/IRCNetwork.h>
#include <znc/Message.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);
  CMessage msg;
  msg.Parse(input);
  CClient client;
  client.OnOtherMessage(&client, &msg);
  return 0;
}