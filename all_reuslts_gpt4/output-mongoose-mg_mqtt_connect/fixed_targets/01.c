#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mongoose.h"

// Dummy callback function
void dummy_fn(struct mg_connection *c, int ev, void *p, void *user_data) {}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct mg_mgr mgr;
  struct mg_mqtt_opts opts;
  func_type *fn = dummy_fn;
  char *fn_data = nullptr;

  mg_mgr_init(&mgr, nullptr);

  FuzzedDataProvider stream(data, size);

  // Consume data for url and fn_data
  std::string url = stream.ConsumeRandomLengthString();
  std::string fn_data_str = stream.ConsumeRemainingBytesAsString();
  fn_data = const_cast<char*>(fn_data_str.c_str());

  // Initialize options with default values
  opts.user_name = nullptr;
  opts.password = nullptr;
  opts.client_id = nullptr;
  opts.protocol_version = 0;
  opts.will_topic = nullptr;
  opts.will_message = nullptr;
  opts.keep_alive = 0;
  opts.clean_session = 0;

  mg_mqtt_connect(&mgr, const_cast<char*>(url.c_str()), &opts, fn, fn_data);

  mg_mgr_free(&mgr);

  return 0;
}