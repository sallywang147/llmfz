#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "am.h"
#include "am_diff.h"
#include "am_diff_files.h"
#include "am_diff_index.h"
#include "am_diff_tree.h"
#include "am_add.h"
#include "am_commit.h"
#include "am_init_db.h"
#include "help.h"
#include "am_ls_files.h"
#include "am_config.h"
#include "am_rerere.h"
#include "am_ls_tree.h"
#include "am_mv.h"
#include "am_status.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int argc = stream.ConsumeIntegral<int>();
  std::vector<std::string> argv;
  for (int i = 0; i < argc; i++) {
    argv.push_back(stream.ConsumeRemainingBytesAsString());
  }
  std::string env = stream.ConsumeRemainingBytesAsString();

  std::vector<char*> argv_ptr;
  for (const auto& arg : argv) {
    argv_ptr.push_back(const_cast<char*>(arg.c_str()));
  }
  argv_ptr.push_back(nullptr);
  char* env_ptr = const_cast<char*>(env.c_str());

  cmd_am(argc, argv_ptr.data(), env_ptr);
  return 0;
}