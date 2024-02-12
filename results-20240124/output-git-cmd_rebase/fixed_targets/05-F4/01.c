#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t num_args = provider.ConsumeIntegralInRange<size_t>(1, 10);
  std::vector<char*> args(num_args + 1);
  for (size_t i = 0; i < num_args; i++) {
    const size_t arg_len = provider.ConsumeIntegralInRange<size_t>(0, 100);
    args[i] = new char[arg_len + 1];
    provider.ConsumeBytes(args[i], arg_len);
    args[i][arg_len] = '\0';
  }
  args[num_args] = nullptr;

  const size_t cmd_len = provider.ConsumeIntegralInRange<size_t>(0, 100);
  char* cmd = new char[cmd_len + 1];
  provider.ConsumeBytes(cmd, cmd_len);
  cmd[cmd_len] = '\0';

  // Fix: call the function `cmd_rebase`
  cmd_rebase(num_args, args.data(), cmd);

  for (size_t i = 0; i < num_args; i++) {
    delete[] args[i];
  }
  delete[] cmd;

  return 0;
}