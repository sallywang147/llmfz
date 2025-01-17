#include <fuzzer/FuzzedDataProvider.h>
#include <rfb/rfb.h>

static bool initialized = false;
static rfbScreenInfoPtr server;
static char *fakeargv[] = {"fuzz_server"};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (!initialized) {
    int fakeargc = 1;
    server = rfbGetScreen(&fakeargc, fakeargv, 400, 300, 8, 3, 4);
    server->frameBuffer = (char*)malloc(400 * 300 * 4);
    rfbInitServer(server);
    initialized = true;
  }

  rfbClientPtr cl = rfbNewClient(server, -1);
  if (cl == NULL) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  std::string clientData = stream.ConsumeRemainingBytesAsString();

  cl->clientData = (void*)clientData.c_str();

  rfbStartOnHoldClient(cl);

  return 0;
}