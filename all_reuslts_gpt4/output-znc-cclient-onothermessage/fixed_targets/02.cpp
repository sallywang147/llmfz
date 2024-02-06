#include <fuzzer/FuzzedDataProvider.h>
#include <znc/Client.h>
#include <znc/Message.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string str = stream.ConsumeRandomLengthString();
  CMessage msg;
  msg.Parse(str);

  CClient client;
  client.OnOtherMessage(&client, &msg);

  return 0;
}