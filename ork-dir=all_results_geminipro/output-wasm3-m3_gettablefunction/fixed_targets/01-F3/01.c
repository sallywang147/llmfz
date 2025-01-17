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
  if (!env) {
    FATAL("m3_NewEnvironment failed");
  }

  IM3Runtime runtime = m3_NewRuntime(env, 128, NULL);
  if (!runtime) {
    FATAL("m3_NewRuntime failed");
  }

  IM3Module module = NULL;
  result = m3_ParseModule(env, &module, data, size);
  if (result != m3Err_none) {
    FATAL("m3_ParseModule failed");
  }

  result = m3_LoadModule(runtime, module);
  if (result != m3Err_none) {
    FATAL("m3_LoadModule failed");
  }

  IM3Function f = NULL;
  result = m3_GetTableFunction(&f, module, 0);
  if (result != m3Err_none) {
    FATAL("m3_GetTableFunction failed");
  }

  m3_CallV(f, 10); // Added the missing closing parenthesis

  m3_FreeModule(module);
  m3_FreeRuntime(runtime);
  m3_FreeEnvironment(env); // Added the call to m3_FreeEnvironment

  return 0;
}