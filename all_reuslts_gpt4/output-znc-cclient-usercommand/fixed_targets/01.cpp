#include <fuzzer/FuzzedDataProvider.h>
#include <znc/Client.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string str = stream.ConsumeRandomLengthString();
  CString cstr(str.c_str());

  CClient client;
  client.UserCommand(&client, &cstr);

  return 0;
}