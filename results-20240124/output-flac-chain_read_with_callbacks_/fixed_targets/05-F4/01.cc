#include <iostream>
#include <thread>
#include <chrono>

#include "chain_reader.h"

extern "C" {
#include "chain_reader.h"
}

int main() {
  std::cout << "Waiting for chain_reader to start..." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));

  chain_read_with_callbacks_();

  return 0;
}