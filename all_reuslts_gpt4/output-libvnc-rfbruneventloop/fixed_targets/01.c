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

  FuzzedDataProvider fuzzed_data(data, size);
  size_t usec = fuzzed_data.ConsumeIntegral<size_t>();
  char runInBackground = fuzzed_data.ConsumeBool();

  rfbRunEventLoop(server, usec, runInBackground);

  return 0;
}