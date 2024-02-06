#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the tmuxproc struct
  struct tmuxproc client;
  client.name = stream.ConsumeRandomLengthString().c_str();
  client.pid = stream.ConsumeIntegral<pid_t>();
  client.event = NULL;

  // Define flags
  int flags = stream.ConsumeIntegral<int>();

  // Initialize the event_base struct
  struct event_base *base = event_base_new();
  if (base == NULL)
    return 0;

  // Define lockfd
  int lockfd = stream.ConsumeIntegral<int>();

  // Define lockfile
  std::string lockfile = stream.ConsumeRandomLengthString();
  
  // Call the function to fuzz
  server_start(&client, flags, base, lockfd, const_cast<char*>(lockfile.c_str()));

  event_base_free(base);

  return 0;
}