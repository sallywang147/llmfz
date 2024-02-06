#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <dwfl.h>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    dwfl_init();
    initialized = true;
  }

  Dwfl* dwfl = dwfl_begin();
  if (dwfl == nullptr) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  std::vector<uint8_t> buffer(provider.ConsumeRemainingBytes());

  Dwfl_Module* module = dwfl_module_create_from_memory(
      dwfl, reinterpret_cast<const char*>(buffer.data()), buffer.size());
  if (module == nullptr) {
    dwfl_end(dwfl);
    return 0;
  }

  Dwfl_Thread* thread = dwfl_thread_create(dwfl, module);
  if (thread == nullptr) {
    dwfl_module_destroy(module);
    dwfl_end(dwfl);
    return 0;
  }

  dwfl_thread_getframes(thread, nullptr, nullptr);

  dwfl_thread_destroy(thread);
  dwfl_module_destroy(module);
  dwfl_end(dwfl);

  return 0;
}