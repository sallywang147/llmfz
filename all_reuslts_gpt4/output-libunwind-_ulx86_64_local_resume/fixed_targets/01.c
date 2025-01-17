#include <fuzzer/FuzzedDataProvider.h>
#include <libunwind.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  unw_addr_space_t as = unw_local_addr_space;

  unw_cursor_t cursor;
  unw_context_t context;
  unw_getcontext(&context);
  unw_init_local(&cursor, &context);

  std::string arg = stream.ConsumeRandomLengthString();
  char *arg_ptr = const_cast<char*>(arg.c_str());

  _ULx86_64_local_resume(as, &cursor, arg_ptr);

  return 0;
}