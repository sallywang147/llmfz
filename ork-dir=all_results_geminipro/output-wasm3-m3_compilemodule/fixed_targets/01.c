#include <stddef.h>
#include <stdint.h>

#include "wasm3.h"

#define FATAL(...) __builtin_trap()

extern "C" {
#include "m3/m3_api_defs.h"
#include "m3/m3_env.h"
#include "m3/m3_exception.h"
#include "m3/m3_module.h"
#include "m3/m3_runtime.h"
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

  result = m3_LinkModule(runtime, module);  // Link the module to the runtime
  if (result != m3Err_none) {
    FATAL("m3_LinkModule failed");
  }

  result = m3_InstantiateModule(runtime, module);  // Instantiate the module
  if (result != m3Err_none) {
    FATAL("m3_InstantiateModule failed");
  }

  char *compiled = m3_CompileModule(module);
  if (!compiled) {
    FATAL("m3_CompileModule failed");
  }

  m3_Free(compiled);
  m3_FreeModule(module);
  m3_FreeRuntime(runtime);
  m3_FreeEnvironment(env);

  return 0;
}