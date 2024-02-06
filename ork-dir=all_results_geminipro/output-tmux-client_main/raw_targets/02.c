#include <fuzzer/FuzzedDataProvider.h>

#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/util.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int client_main(struct event_base * base, int argc, char ** argv, size_t flags, int feat) {
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);

  struct event_base *base = event_base_new();
  if (!base) {
    return 0;
  }

  int argc = fdp.ConsumeIntegral<int>();
  std::vector<char *> argv_vec;
  for (int i = 0; i < argc; i++) {
    size_t arg_len = fdp.ConsumeIntegralInRange<size_t>(0, 1024);
    std::string arg_str = fdp.ConsumeBytesAsString(arg_len);
    argv_vec.push_back((char *)arg_str.c_str());
  }
  char **argv = argv_vec.data();

  size_t flags = fdp.ConsumeIntegral<size_t>();
  int feat = fdp.ConsumeIntegral<int>();

  client_main(base, argc, argv, flags, feat);

  event_base_free(base);

  return 0;
}