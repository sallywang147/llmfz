#include <elfutils/libdwfl.h>
#include <fuzzer/FuzzedDataProvider.h>

// Define a callback function that matches the required signature
static int callback(Dwfl_Frame *frame, void *arg) {
  return DWARF_CB_OK;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize libdwfl
  Dwfl_Callbacks callbacks = {
    .find_debuginfo = dwfl_standard_find_debuginfo,
    .section_address = dwfl_offline_section_address,
  };
  Dwfl *dwfl = dwfl_begin(&callbacks);

  // Create a Dwfl_Module
  Dwfl_Module *mod = dwfl_report_offline(dwfl, "fuzz", "fuzz", -1);

  // Create a Dwfl_Thread
  Dwfl_Thread *thread = dwfl_pid_to_thread(dwfl, getpid());

  // Get the argument for dwfl_thread_getframes
  std::string arg = stream.ConsumeRandomLengthString();
  char *arg_ptr = arg.c_str();

  // Call the function to fuzz
  int result = dwfl_thread_getframes(thread, callback, arg_ptr);

  // Clean up
  dwfl_end(dwfl);

  return 0;
}