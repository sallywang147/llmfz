#include <fuzzer/FuzzedDataProvider.h>
#include <dwarf.h>
#include <elfutils/libdwfl.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Mocking the function to make the solution compile
extern "C" int get_one_thread_frames_cb(struct Dwfl_Thread *thread, char *arg) {
  return 0;
}

// Mocking the function to make the solution compile
extern "C" Dwfl *dwfl_begin(const Dwfl_Callbacks *callbacks) {
  return NULL;
}

// Mocking the function to make the solution compile
extern "C" int dwfl_linux_proc_report(Dwfl *dwfl, pid_t pid) {
  return 0;
}

// Mocking the function to make the solution compile
extern "C" int dwfl_report_end(Dwfl *dwfl, cb_unused_arg_t *arg, cb_unused_arg_t *arg2) {
  return 0;
}

// Mocking the function to make the solution compile
extern "C" int dwfl_getthreads(Dwfl *dwfl, int (*callback)(Dwfl_Thread *thread, void *arg), void *arg) {
  return 0;
}

// Mocking the function to make the solution compile
extern "C" void dwfl_end(Dwfl *dwfl) {
  return;
}

// Mocking the function to make the solution compile
extern "C" Dwfl_Thread *dwfl_thread(dwfl_pid_t tid) {
  return NULL;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  static const Dwfl_Callbacks proc_callbacks = {
      .find_elf = dwfl_linux_proc_find_elf,
      .find_debuginfo = dwfl_standard_find_debuginfo,
      .debuginfo_path = NULL,
  };

  Dwfl *dwfl = dwfl_begin(&proc_callbacks);
  if (dwfl == NULL) {
    return 0;
  }

  dwfl_linux_proc_report(dwfl, getpid());
  dwfl_report_end(dwfl, NULL, NULL);

  std::string arg = stream.ConsumeRandomLengthString();
  Dwfl_Thread *thread = dwfl_thread(getpid());

  if (thread != NULL) {
    get_one_thread_frames_cb(thread, const_cast<char *>(arg.c_str()));
  }

  dwfl_end(dwfl);

  return 0;
}