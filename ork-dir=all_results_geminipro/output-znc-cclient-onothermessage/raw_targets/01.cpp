#include <stdint.h>
#include <znc/Client.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);
  CMessage msg;
  msg.Parse(input);
  CClient client;
  client.OnOtherMessage(NULL, &msg);
  return 0;
}