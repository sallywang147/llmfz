#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mongoose.h"

// Dummy function to be used as callback
void dummy_fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct mg_mgr mgr;
  mg_mgr_init(&mgr);

  std::string url = stream.ConsumeRandomLengthString();
  std::string fn_data = stream.ConsumeRandomLengthString();
  std::string fmt = stream.ConsumeRandomLengthString();

  mg_ws_connect(&mgr, const_cast<char*>(url.c_str()), dummy_fn, const_cast<char*>(fn_data.c_str()), const_cast<char*>(fmt.c_str()));

  mg_mgr_free(&mgr);

  return 0;
}