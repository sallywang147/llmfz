#include <stddef.h>
#include <stdint.h>

#include "wasm3.h"

#define FATAL(...) __builtin_trap()

extern "C" {
#include <stdio.h>
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
          result = m3_FindFunction(&f, runtime, "fib");
          /* TODO:
          if (f) {
              m3_CallV (f, 10);
          }*/
        } else {
          m3_FreeModule(module);
        }
      }

      // Call op_CallIndirect.
      char *argv[1] = {NULL};
      int argc = 0;
      struct M3MemoryHeader header = {0};
      size_t size = 0;
      double d = 0.0;
      char *r = op_CallIndirect(argv, &argc, &header, size, d);
      if (r != NULL) {
        FATAL("op_CallIndirect returned %s", r);
      }

      m3_FreeRuntime(runtime);
    }
    m3_FreeEnvironment(env);
  }

  return 0;
}