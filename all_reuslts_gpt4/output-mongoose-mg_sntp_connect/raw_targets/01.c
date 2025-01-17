#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mongoose.h"

void dummy_func(struct mg_connection *c, int ev, void *ev_data, void *user_data) {
  // This is a dummy function to pass as a parameter.
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct mg_mgr mgr;
  mg_mgr_init(&mgr, NULL);

  std::string url = stream.ConsumeRandomLengthString();
  char* url_ptr = const_cast<char*>(url.c_str());

  func_type* fn = &dummy_func;

  std::string fnd = stream.ConsumeRandomLengthString();
  char* fnd_ptr = const_cast<char*>(fnd.c_str());

  struct mg_connection* connection = mg_sntp_connect(&mgr, url_ptr, fn, fnd_ptr);

  mg_mgr_free(&mgr);

  return 0;
}