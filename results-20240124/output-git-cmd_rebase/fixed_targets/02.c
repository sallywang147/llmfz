#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include <libfuzzer/libfuzzer_macro.h>
#include <git2.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int argc = stream.ConsumeIntegral<int>();
  std::vector<char*> argv;
  for (int i = 0; i < argc; i++) {
    const std::string arg = stream.ConsumeRemainingBytesAsString();
    argv.push_back(const_cast<char*>(arg.c_str()));
  }
  const std::string command = stream.ConsumeRemainingBytesAsString();
  if (command == "branch") {
    cmd_branch(argc, argv.data());
  } else if (command == "diff") {
    cmd_diff(argc, argv.data());
  } else if (command == "diff-files") {
    cmd_diff_files(argc, argv.data());
  } else if (command == "diff-tree") {
    cmd_diff_tree(argc, argv.data());
  } else if (command == "diff-index") {
    cmd_diff_index(argc, argv.data());
  } else if (command == "add") {
    cmd_add(argc, argv.data());
  } else if (command == "commit") {
    cmd_commit(argc, argv.data());
  } else if (command == "init-db") {
    cmd_init_db(argc, argv.data());
  } else if (command == "ls-files") {
    cmd_ls_files(argc, argv.data());
  } else if (command == "config") {
    cmd_config(argc, argv.data());
  } else if (command == "rerere") {
    cmd_rerere(argc, argv.data());
  } else if (command == "ls-tree") {
    cmd_ls_tree(argc, argv.data());
  } else if (command == "mv") {
    cmd_mv(argc, argv.data());
  } else if (command == "status") {
    cmd_status(argc, argv.data());
  } else if (command == "rebase") {
    cmd_rebase(argc, argv.data(), const_cast<char*>(command.c_str()));
  }
  return 0;
}