#include <elfutils/libdwfl.h>
#include <fuzzer/FuzzedDataProvider.h>

// Callback function for dwfl_getthread_frames
static int frame_callback(Dwfl_Frame *state, void *arg) {
  return DWARF_CB_OK;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize libdwfl
  char *debuginfo_path = NULL;
  Dwfl_Callbacks callbacks = {
      .find_debuginfo = dwfl_standard_find_debuginfo,
      .debuginfo_path = &debuginfo_path,
      .section_address = dwfl_offline_section_address,
  };

  Dwfl *dwfl = dwfl_begin(&callbacks);
  if (dwfl == NULL) {
    return 0;
  }

  // Extract tid from the fuzzer input
  int tid = stream.ConsumeIntegral<int>();

  // Extract arg from the fuzzer input
  std::string arg = stream.ConsumeRandomLengthString();
  char *arg_ptr = arg.c_str();

  // Call dwfl_getthread_frames
  dwfl_getthread_frames(dwfl, tid, frame_callback, arg_ptr);

  // Clean up
  dwfl_end(dwfl);

  return 0;
}