#include <stddef.h>
#include <stdint.h>

#include "wasm3.h"

#define FATAL(...) __builtin_trap()

extern "C" {
#include "fuzzer.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  M3Result result = m3Err_none;

  if (size < 8 || size > 256 * 1024) {
    return 0;
  }

  IM3Environment env = m3_NewEnvironment();
  if (env) {
    IM3Runtime runtime = m3_NewRuntime(env, 128, NULL);
    if (runtime) {
      IM3Module module = NULL;
      result = m3_ParseModule(env, &module, data, size);
      if (module) {
        result = m3_LoadModule(runtime, module);
        if (result == 0) {
          IM3Function f = NULL;
          result = m3_GetTableFunction(&f, module, 0);
          if (f) {
              m3_CallV (f, 10);
          }
        } else {
          m3_FreeModule(module);
        }
      }

      m3_FreeRuntime(runtime);
    }
    m3_FreeEnvironment(env);
  }

  return 0;
}