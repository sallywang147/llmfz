#include <fuzzer/FuzzedDataProvider.h>
#include <rfb/rfb.h>

static int initialized = 0;
rfbScreenInfoPtr server;
char *fakeargv[] = {"fuzz_server"};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (initialized == 0) {
    int fakeargc = 1;
    server = rfbGetScreen(&fakeargc, fakeargv, 400, 300, 8, 3, 4);
    server->frameBuffer = (char*)malloc(400 * 300 * 4);
    rfbInitServer(server);
    initialized = 1;
  }

  FuzzedDataProvider stream(data, size);

  std::string host = stream.ConsumeRandomLengthString();
  int port = stream.ConsumeIntegral<int>();

  rfbClientPtr cl = rfbReverseConnection(server, (char*)host.c_str(), port);
  if (cl != NULL) {
    rfbClientConnectionGone(cl);
  }

  return 0;
}