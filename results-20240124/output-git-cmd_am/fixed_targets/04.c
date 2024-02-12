#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fuzzer/FuzzedDataProvider.h>
#include <string>
#include <vector>

extern "C" {
#include "am.h"  // Include the header file for the 'cmd_am' function.
#include "cmd-status.h"
#include "cmd-add.h"
#include "cmd-commit.h"
#include "cmd-init-db.h"
#include "cmd-branch.h"
#include "cmd-diff.h"
#include "cmd-diff-files.h"
#include "cmd-diff-tree.h"
#include "cmd-diff-index.h"
#include "cmd-ls-files.h"
#include "cmd-config.h"
#include "cmd-rerere.h"
#include "cmd-ls-tree.h"
#include "cmd-mv.h"
#include "load-builtin-commands.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t num_args = stream.ConsumeIntegralInRange<size_t>(0, 10);
  std::vector<std::string> args(num_args);
  for (size_t i = 0; i < num_args; i++) {
    args[i] = stream.ConsumeRemainingBytesAsString();
  }

  std::vector<char*> c_args;
  c_args.reserve(num_args + 1);
  for (const std::string& arg : args) {
    c_args.push_back(const_cast<char*>(arg.c_str()));
  }
  c_args.push_back(nullptr);

  cmd_am(num_args, c_args.data(), nullptr);
  return 0;
}