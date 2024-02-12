#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>
#include <string>
#include <vector>

extern "C" {
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

void cmd_rebase(int argc, char** argv, char* command);
void cmd_status(int argc, char** argv, char* command);
void cmd_add(int argc, char** argv, char* command);
void cmd_commit(int argc, char** argv, char* command);
void cmd_init_db(int argc, char** argv, char* command);
void cmd_branch(int argc, char** argv, char* command);
void cmd_diff(int argc, char** argv, char* command);
void cmd_diff_files(int argc, char** argv, char* command);
void cmd_diff_tree(int argc, char** argv, char* command);
void cmd_diff_index(int argc, char** argv, char* command);
void load_builtin_commands(void);
void cmd_ls_files(int argc, char** argv, char* command);
void cmd_config(int argc, char** argv, char* command);
void cmd_rerere(int argc, char** argv, char* command);
void cmd_ls_tree(int argc, char** argv, char* command);
void cmd_mv(int argc, char** argv, char* command);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int argc = stream.ConsumeIntegral<int>();
  std::vector<std::string> argv;
  for (int i = 0; i < argc; i++) {
    argv.emplace_back(stream.ConsumeRandomLengthString());
  }
  char** argv_ptr = new char*[argc];
  for (int i = 0; i < argc; i++) {
    argv_ptr[i] = const_cast<char*>(argv[i].c_str());
  }
  const std::string command = stream.ConsumeRandomLengthString();
  char* command_ptr = const_cast<char*>(command.c_str());
  if (command == "rebase") {
    cmd_rebase(argc, argv_ptr, command_ptr);
  } else if (command == "status") {
    cmd_status(argc, argv_ptr, command_ptr);
  } else if (command == "add") {
    cmd_add(argc, argv_ptr, command_ptr);
  } else if (command == "commit") {
    cmd_commit(argc, argv_ptr, command_ptr);
  } else if (command == "init-db") {
    cmd_init_db(argc, argv_ptr, command_ptr);
  } else if (command == "branch") {
    cmd_branch(argc, argv_ptr, command_ptr);
  } else if (command == "diff") {
    cmd_diff(argc, argv_ptr, command_ptr);
  } else if (command == "diff-files") {
    cmd_diff_files(argc, argv_ptr, command_ptr);
  } else if (command == "diff-tree") {
    cmd_diff_tree(argc, argv_ptr, command_ptr);
  } else if (command == "diff-index") {
    cmd_diff_index(argc, argv_ptr, command_ptr);
  } else if (command == "ls-files") {
    cmd_ls_files(argc, argv_ptr, command_ptr);
  } else if (command == "config") {
    cmd_config(argc, argv_ptr, command_ptr);
  } else if (command == "rerere") {
    cmd_rerere(argc, argv_ptr, command_ptr);
  } else if (command == "ls-tree") {
    cmd_ls_tree(argc, argv_ptr, command_ptr);
  } else if (command == "mv") {
    cmd_mv(argc, argv_ptr, command_ptr);
  }
  delete[] argv_ptr;
  return 0;
}

int main() {
  load_builtin_commands();
  return 0;
}