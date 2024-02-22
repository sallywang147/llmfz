/*
 * A fuzzer focused on C string -> Javascript String.
 */

#include "aliased_buffer.h"
#include "env-inl.h"
#include "fuzz_helper.h"
#include "js_native_api.h"
#include "js_native_api_v8.h"
#include "libplatform/libplatform.h"
#include "node.h"
#include "node_api_internals.h"
#include "node_internals.h"
#include "node_platform.h"
#include "node_url.h"
#include "util-inl.h"
#include "v8.h"
#include <stdlib.h>

using node::AliasedBufferBase;

/* General set up */
using ArrayBufferUniquePtr = std::unique_ptr<node::ArrayBufferAllocator, decltype(&node::FreeArrayBufferAllocator)>;
using TracingAgentUniquePtr = std::unique_ptr<node::tracing::Agent>;
using NodePlatformUniquePtr = std::unique_ptr<node::NodePlatform>;

static TracingAgentUniquePtr tracing_agent;
static NodePlatformUniquePtr platform;
static uv_loop_t current_loop;
static napi_env addon_env;

inline napi_env NewEnv(v8::Local<v8::Context> context, const std::string &module_filename, int32_t module_api_version);

static void free_string(node_api_nogc_env env, void *data, void *hint) { free(data); }

extern "C" int LLVMFuzzerInitialize(int *argc, char ***argv) {
  uv_os_unsetenv("NODE_OPTIONS");
  std::vector<std::string> node_argv{"fuzz_string_conversion"};
  std::vector<std::string> exec_argv;
  std::vector<std::string> errors;

  node::InitializeNodeWithArgs(&node_argv, &exec_argv, &errors);

  tracing_agent = std::make_unique<node::tracing::Agent>();
  node::tracing::TraceEventHelper::SetAgent(tracing_agent.get());
  node::tracing::TracingController *tracing_controller = tracing_agent->GetTracingController();
  CHECK_EQ(0, uv_loop_init(&current_loop));
  static constexpr int kV8ThreadPoolSize = 4;
  platform.reset(new node::NodePlatform(kV8ThreadPoolSize, tracing_controller));
  v8::V8::InitializePlatform(platform.get());
  cppgc::InitializeProcess(platform->GetPageAllocator());
  v8::V8::Initialize();
  return 0;
}

class FuzzerFixtureHelper {
public:
  v8::Isolate *isolate_;
  ArrayBufferUniquePtr allocator;

  FuzzerFixtureHelper() : allocator(ArrayBufferUniquePtr(node::CreateArrayBufferAllocator(), &node::FreeArrayBufferAllocator)) {
    isolate_ = NewIsolate(allocator.get(), &current_loop, platform.get());
    CHECK_NOT_NULL(isolate_);
    isolate_->Enter();
  };

  void Teardown() {
    platform->DrainTasks(isolate_);
    isolate_->Exit();
    platform->UnregisterIsolate(isolate_);
    isolate_->Dispose();
    isolate_ = nullptr;
  }
};

void EnvTest(v8::Isolate *isolate_, char *env_string, size_t size) {
  const v8::HandleScope handle_scope(isolate_);
  Argv argv;

  node::EnvironmentFlags::Flags flags = node::EnvironmentFlags::kDefaultFlags;
  auto isolate = handle_scope.GetIsolate();
  v8::Local<v8::Context> context_ = node::NewContext(isolate);
  context_->Enter();

  node::IsolateData *isolate_data_ = node::CreateIsolateData(isolate, &current_loop, platform.get());
  std::vector<std::string> args(*argv, *argv + 1);
  std::vector<std::string> exec_args(*argv, *argv + 1);
  node::Environment *environment_ = node::CreateEnvironment(isolate_data_, context_, args, exec_args, flags);
  node::Environment *envi = environment_;
  SetProcessExitHandler(envi, [&](node::Environment *env_, int exit_code) { node::Stop(envi); });
  node::LoadEnvironment(envi, "");

  napi_addon_register_func init = [](napi_env env, napi_value exports) {
    addon_env = env;
    return exports;
  };
  v8::Local<v8::Object> module_obj = v8::Object::New(isolate);
  v8::Local<v8::Object> exports_obj = v8::Object::New(isolate);
  napi_module_register_by_symbol(exports_obj, module_obj, context_, init, NAPI_VERSION);
  size_t copied1, copied2;
  bool copied3;
  napi_value output1, output2, output3, output4, output5, output6, output7, output8, output9, output10, output11, output12;
  char *buf1 = (char *)malloc(size);
  char *buf2 = (char *)malloc(size);
  napi_create_string_utf8(addon_env, env_string, size, &output1);
  napi_get_value_string_utf8(addon_env, output1, buf1, size, &copied1);
  napi_create_string_latin1(addon_env, env_string, size, &output2);
  napi_get_value_string_latin1(addon_env, output2, buf2, size, &copied2);

  char *string_copy;
  const size_t actual_length = (size == NAPI_AUTO_LENGTH ? strlen(env_string) : size);
  const size_t length_bytes = (actual_length + 1) * sizeof(*string_copy);
  string_copy = (char *)malloc(length_bytes);
  memcpy(string_copy, env_string, length_bytes);
  string_copy[actual_length] = 0;

  // node_api_create_external_string_latin1(addon_env, string_copy, size, free_string, NULL, output3, &copied3);

  node_api_symbol_for(addon_env, env_string, size, &output4);

  napi_set_named_property(addon_env, output1, env_string, output2); // could use other napi_values than 'output1'

  napi_get_named_property(addon_env, output1, env_string, &output6); // could use other napi_values than 'output1'

  napi_has_named_property(addon_env, output1, env_string, &copied3); // could use other napi_values than 'output1'

  napi_get_property_names(addon_env, output1, &output7); // could use other napi_values than 'output1'

  napi_has_property(addon_env, output1, output2, &copied3); // could use other napi_values than 'output1/2'

  napi_get_property(addon_env, output1, output2, &output8); // could use other napi_values than 'output1/2'

  napi_delete_property(addon_env, output1, output2, &copied3); // could use other napi_values than 'output1/2'

  napi_has_own_property(addon_env, output1, output2, &copied3); // could use other napi_values than 'output1/2'

  napi_create_type_error(addon_env, output1, output2, &output9); // could use other napi_values than 'output1/2'

  napi_create_range_error(addon_env, output1, output2, &output10); // could use other napi_values than 'output1/2'

  node_api_create_syntax_error(addon_env, output1, output2, &output11); // could use other napi_values than 'output1/2'

  napi_run_script(addon_env, output2, &output12); // could use other napi_values than 'output2'

  // napi_is_array(addon_env, output1, copied3); // could use other napi_values than 'output1'

  free(string_copy);
  free(buf1);
  free(buf2);

  // Cleanup!
  node::FreeEnvironment(environment_);
  node::FreeIsolateData(isolate_data_);
  context_->Exit();
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data2, size_t size) {
  FuzzerFixtureHelper ffh;
  std::string s(reinterpret_cast<const char *>(data2), size);
  EnvTest(ffh.isolate_, (char *)s.c_str(), size);
  ffh.Teardown();
  return 0;
}