#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mongoose.h"

// Define the callback function type
typedef void (*func_type)(struct mg_connection *, int, void *, void *);

// Dummy callback function for testing
void dummy_callback(struct mg_connection *nc, int ev, void *ev_data, void *user_data) {
    // Do nothing
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  struct mg_mgr mgr;
  mg_mgr_init(&mgr, NULL);

  FuzzedDataProvider stream(data, size);

  // Extract url string
  std::string url = stream.ConsumeRandomLengthString();
  // Extract fnd string
  std::string fnd = stream.ConsumeRemainingBytesAsString();

  // Call the function to fuzz
  struct mg_connection *conn = mg_sntp_connect(&mgr, const_cast<char*>(url.c_str()), dummy_callback, const_cast<char*>(fnd.c_str()));

  mg_mgr_free(&mgr);

  return 0;
}