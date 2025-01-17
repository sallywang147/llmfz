#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "wpa_supplicant/wpa_supplicant.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct wpa_global* global = wpa_supplicant_init(&stream);
  if (global == nullptr) {
    return 0;
  }

  wpa_supplicant_run(global);
  wpa_supplicant_deinit(global);
  return 0;
}

struct wpa_global* wpa_supplicant_init(FuzzedDataProvider* stream) {
  struct wpa_global* global = wpa_supplicant_init2();
  if (global == nullptr) {
    return nullptr;
  }

  const char* conf_file = stream->ConsumeRandomLengthString().c_str();
  if (wpa_supplicant_conf_read(global, conf_file)) {
    wpa_supplicant_deinit(global);
    return nullptr;
  }

  return global;
}