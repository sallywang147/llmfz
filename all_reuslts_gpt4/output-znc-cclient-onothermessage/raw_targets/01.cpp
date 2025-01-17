#include <fuzzer/FuzzedDataProvider.h>
#include <znc/Client.h>
#include <znc/Message.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string str1 = stream.ConsumeRandomLengthString();
  CMessage msg1(str1);

  std::string str2 = stream.ConsumeRemainingBytesAsString();
  CMessage msg2(str2);

  CClient client;
  client.OnOtherMessage(&client, &msg1);
  client.OnOtherMessage(&client, &msg2);

  return 0;
}