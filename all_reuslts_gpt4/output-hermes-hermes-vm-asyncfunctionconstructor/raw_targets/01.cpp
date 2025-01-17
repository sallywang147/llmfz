#include <fuzzer/FuzzedDataProvider.h>
#include <hermes/hermes.h>
#include <hermes/VM/Runtime.h>
#include <hermes/VM/NativeArgs.h>

using hermes::vm::Runtime;
using hermes::vm::NativeArgs;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string str = stream.ConsumeRandomLengthString();
  char *char_ptr = const_cast<char*>(str.c_str());

  std::unique_ptr<Runtime> runtime = Runtime::create();

  // Create an empty NativeArgs object
  NativeArgs args = NativeArgs::empty();

  hermes::vm::asyncFunctionConstructor(char_ptr, runtime.get(), &args);

  return 0;
}