#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

extern "C" {
#include "builtin/builtin.h"
#include "builtin/branch.h"
#include "builtin/commit.h"
#include "builtin/config.h"
#include "builtin/diff.h"
#include "builtin/diff-files.h"
#include "builtin/diff-index.h"
#include "builtin/diff-tree.h"
#include "builtin/init-db.h"
#include "builtin/ls-files.h"
#include "builtin/ls-tree.h"
#include "builtin/merge.h"
#include "builtin/mv.h"
#include "builtin/rerere.h"
#include "builtin/status.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int argc = stream.ConsumeIntegral<int>();
  std::vector<char*> argv;
  argv.reserve(argc);
  for (int i = 0; i < argc; i++) {
    const std::string arg = stream.ConsumeRemainingBytesAsString();
    argv.push_back(strdup(arg.c_str()));
  }
  const char* merge_path = stream.ConsumeRemainingBytesAsString().c_str();
  int ret = cmd_merge(argc, argv.data(), const_cast<char*>(merge_path));
  for (int i = 0; i < argc; i++) {
    free(argv[i]);
  }
  return ret;
}