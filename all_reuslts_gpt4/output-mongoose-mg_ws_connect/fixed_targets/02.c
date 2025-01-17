#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mongoose.h"

// Define a dummy function to pass to mg_ws_connect
void dummy_fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  // Do nothing
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    mg_mgr_init();
    initialized = true;
  }

  struct mg_mgr mgr;
  mg_mgr_init(&mgr, NULL);

  FuzzedDataProvider provider(data, size);

  // Consume data for the url
  std::string url = provider.ConsumeRandomLengthString();
  // Consume data for the fn_data
  std::string fn_data = provider.ConsumeRandomLengthString();
  // Consume data for the fmt
  std::string fmt = provider.ConsumeRandomLengthString();

  mg_ws_connect(&mgr, (char*)url.c_str(), dummy_fn, (char*)fn_data.c_str(), (char*)fmt.c_str());

  mg_mgr_free(&mgr);

  return 0;
}