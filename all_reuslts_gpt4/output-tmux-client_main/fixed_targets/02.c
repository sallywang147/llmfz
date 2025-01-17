#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize parameters for client_main function
  struct event_base *base = event_base_new();
  size_t flags = stream.ConsumeIntegral<size_t>();
  int feat = stream.ConsumeIntegral<int>();

  // Prepare argv parameter
  std::vector<std::string> args;
  while (stream.remaining_bytes() > 0) {
    args.push_back(stream.ConsumeRandomLengthString());
  }

  // The first argument is usually the program name, let's simulate that
  if (!args.empty()) {
    args[0] = "fuzzer";
  }

  int argc = args.size();
  std::vector<char*> argv;
  for (auto& arg : args) {
    argv.push_back(const_cast<char*>(arg.c_str()));
  }

  // Call the target function
  client_main(base, argc, argv.data(), flags, feat);

  // Clean up
  event_base_free(base);

  return 0;
}