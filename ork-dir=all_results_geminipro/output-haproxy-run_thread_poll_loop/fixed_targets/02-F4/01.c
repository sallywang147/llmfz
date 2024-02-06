#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <vector>

extern "C" {
#include "libFuzzer.h"
}

struct ThreadData {
  char* data;
  size_t size;
};

char* run_thread_poll_loop(char* data) {
  return data;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ThreadData thread_data;
  thread_data.data = (char*)data;
  thread_data.size = size;
  std::vector<std::thread> threads;
  for (int i = 0; i < 4; i++) {
    threads.push_back(std::thread(run_thread_poll_loop, &thread_data));
  }
  for (auto& thread : threads) {
    thread.join();
  }
  return 0;
}