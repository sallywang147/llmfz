#include <hermes/hermes.h>

extern "C" {
#include "hermes_bindings.h"
}

int main() {
  hermes::vm::Runtime runtime;
  hermes::vm::GlobalObject global = runtime.global();
  hermes::vm::Handle<hermes::vm::StringPrimitive> hello = runtime.makeHandle(hermes::vm::StringPrimitive::createAsciiString(&runtime, "Hello, World!"));
  global.setProperty(runtime, "hello", hello);
  hermes::vm::Handle<hermes::vm::StringPrimitive> code = runtime.makeHandle(hermes::vm::StringPrimitive::createAsciiString(&runtime, "console.log(hello);"));
  hermes::vm::Handle<hermes::vm::Callable> fn = runtime.makeHandle(hermes::vm::functionConstructor(&runtime, code));
  fn->call(&runtime, global);
  return 0;
}