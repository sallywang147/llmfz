#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "mongoose.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string url = stream.ConsumeRemainingBytesAsString();
  struct mg_mgr mgr;
  mg_mgr_init(&mgr);
  struct mg_mqtt_opts opts;
  mg_mqtt_opts_init(&opts);
  struct mg_connection * c = mg_mqtt_connect(&mgr, url.c_str(), &opts, nullptr,
                                            nullptr);
  mg_mqtt_disconnect(c);
  mg_mgr_free(&mgr);
  return 0;
}