#include <fuzzer/FuzzedDataProvider.h>
#include "mongoose.h"

// Define a dummy callback function
void dummy_func(struct mg_connection *c, int ev, void *p, void *user_data) {}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  struct mg_mgr mgr;
  mg_mgr_init(&mgr, NULL);

  std::string url = stream.ConsumeRandomLengthString();
  struct mg_mqtt_opts opts;
  opts.user_name = stream.ConsumeRandomLengthString().c_str();
  opts.password = stream.ConsumeRandomLengthString().c_str();
  opts.client_id = stream.ConsumeRandomLengthString().c_str();
  opts.will_topic = stream.ConsumeRandomLengthString().c_str();
  opts.will_message = stream.ConsumeRandomLengthString().c_str();
  opts.keep_alive = stream.ConsumeIntegral<unsigned short>();
  opts.clean_session = stream.ConsumeBool();
  opts.use_ssl = stream.ConsumeBool();

  std::string fn_data = stream.ConsumeRemainingBytesAsString();

  mg_mqtt_connect(&mgr, (char *)url.c_str(), &opts, dummy_func, (char *)fn_data.c_str());

  mg_mgr_free(&mgr);

  return 0;
}