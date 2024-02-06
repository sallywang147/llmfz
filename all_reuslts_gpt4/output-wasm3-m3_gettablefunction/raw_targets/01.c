#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "m3_api_defs.h"
#include "m3_env.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  IM3Environment env = m3_NewEnvironment();
  if (!env) {
    return 0;
  }

  IM3Runtime runtime = m3_NewRuntime(env, 1024, NULL);
  if (!runtime) {
    m3_FreeEnvironment(env);
    return 0;
  }

  IM3Module module = m3_ParseModule(env, stream.ConsumeRemainingBytes().data(), size);
  if (!module) {
    m3_FreeRuntime(runtime);
    m3_FreeEnvironment(env);
    return 0;
  }

  m3_LoadModule(runtime, module);

  struct M3Function* function = NULL;
  int index = stream.ConsumeIntegral<int>();

  m3_GetTableFunction(&function, module, index);

  m3_FreeRuntime(runtime);
  m3_FreeEnvironment(env);

  return 0;
}