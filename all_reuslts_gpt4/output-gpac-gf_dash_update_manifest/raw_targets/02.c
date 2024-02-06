#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gpac/constants.h"
#include "gpac/dash.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    gf_sys_init(GF_MemTrackerNone);
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);
  std::string manifest = provider.ConsumeRemainingBytesAsString();

  GF_DASHFileIOSession session;
  GF_Err e;
  GF_DASHFileIO dashio;
  memset(&dashio, 0, sizeof(GF_DASHFileIO));
  dashio.solved_template = gf_dash_solve_representation_template;
  dashio.get_full_url = gf_dash_get_url;
  dashio.on_dash_event = gf_dash_on_event;
  dashio.on_filter_event = gf_dash_io_on_filter_event;

  GF_DASHClient* dash = gf_dash_new(&dashio, 0, 1000, 1);
  if (dash == nullptr) {
    return 0;
  }

  e = gf_dash_open(dash, manifest.c_str(), 0);
  if (e != GF_OK) {
    gf_dash_del(dash);
    return 0;
  }

  gf_dash_update_manifest(dash);
  gf_dash_del(dash);

  return 0;
}