#include <fuzzer/FuzzedDataProvider.h>
#include <znc/Client.h>
#include <znc/String.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  std::string str = stream.ConsumeRemainingBytesAsString();
  CString cstr(str.c_str(), str.size());

  CClient client;
  client.ReadLine(&client, &cstr);

  return 0;
}