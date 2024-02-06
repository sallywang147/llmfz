#include <fuzzer/FuzzedDataProvider.h>
#include <znc/Client.h>
#include <znc/IRCSock.h>
#include <znc/ZNCString.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  CString line = stream.ConsumeRandomLengthString().c_str();

  CClient* client = new CClient;
  client->ReadLine(line);

  delete client;
  
  return 0;
}